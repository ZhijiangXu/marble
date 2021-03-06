//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2011      Konstantin Oblaukhov <oblaukhov.konstantin@gmail.com>
//

#include "OsmTagTagHandler.h"

#include "OsmElementDictionary.h"
#include "OsmParser.h"

#include "GeoDataDocument.h"
#include "GeoDataPlacemark.h"
#include "GeoDataParser.h"
#include "GeoDataLineString.h"
#include "GeoDataStyle.h"
#include "GeoDataExtendedData.h"
#include "osm/OsmPlacemarkData.h"

#include "MarbleDebug.h"

namespace Marble
{

namespace osm
{
static GeoTagHandlerRegistrar osmTagTagHandler( GeoParser::QualifiedName( osmTag_tag, "" ),
                                                new OsmTagTagHandler() );

static QStringList tagBlackList = QStringList() << "created_by";

GeoNode* OsmTagTagHandler::parse( GeoParser &geoParser ) const
{
    Q_ASSERT( dynamic_cast<OsmParser *>( &geoParser ) != 0 );
    OsmParser &parser = static_cast<OsmParser &>( geoParser );

    Q_ASSERT( parser.isStartElement() );

    GeoStackItem parentItem = parser.parentElement();
    GeoDataDocument* doc = geoDataDoc( parser );
    QString key = parser.attribute( "k" );
    QString value = parser.attribute( "v" );


    if ( tagBlackList.contains( key ) )
        return 0;

    GeoDataGeometry * geometry = parentItem.nodeAs<GeoDataGeometry>();
    if ( !geometry )
        return 0;

    GeoDataGeometry *placemarkGeometry = geometry;

    //If node geometry is part of multigeometry -> go up to placemark geometry.
    while( dynamic_cast<GeoDataMultiGeometry*>(placemarkGeometry->parent()) )
        placemarkGeometry = dynamic_cast<GeoDataMultiGeometry*>(placemarkGeometry->parent());
    GeoDataPlacemark *placemark = dynamic_cast<GeoDataPlacemark*>(placemarkGeometry->parent());
    Q_ASSERT( placemark );

    // Getting the placemark's osm data
    OsmPlacemarkData &osmData =  placemark->osmData();

    // Inserting the tag into the placemark's tag hash
    osmData.addTag( key, value );

    if ( key == "name" ) {
        // If placemark is not in the document, add it.
        if ( !placemark->parent() ) {
            if ( parentItem.represents( osmTag_node ) ) {
                placemark = createPOI( doc, geometry, osmData );
            }
            else if ( parentItem.represents( osmTag_way ) ) {
                doc->append( placemark );
            }
            else {
                return 0;
            }
        }
        placemark->setName( value );
        return 0;
    }

    // Ways or relations can represent closed areas such as buildings
    if ( parentItem.represents( osmTag_way ) || parentItem.represents( osmTag_relation ) ) {
        if( !dynamic_cast<GeoDataPolygon*>( geometry ) && parser.tagNeedArea( key + '=' + value ) ) {
            //Convert area ways or relations to polygons
            GeoDataLineString *polyline = dynamic_cast<GeoDataLineString *>( geometry );
            Q_ASSERT( polyline );
            if ( placemark->parent() ) {
                doc->remove( doc->childPosition( placemark ) );
            }
            parser.addDummyPlacemark( placemark );
            placemark = new GeoDataPlacemark( *placemark );
            GeoDataPolygon *polygon = new GeoDataPolygon;
            GeoDataLinearRing ring = GeoDataLinearRing ( *polyline );
            polygon->setOuterBoundary( ring );
            //FIXME: Dirty hack to change placemark associated with node, for parsing purposes.
            polyline->setParent( placemark );
            placemark->setGeometry( polygon );
            doc->append( placemark );
        }
        if ( key == "building" && value == "yes" && placemark->visualCategory() == GeoDataFeature::Default )
        {
            placemark->setVisualCategory( GeoDataFeature::Building );
            placemark->setVisible( true );
        }
    }
    else if ( parentItem.represents( osmTag_node ) ) //POI
    {
        GeoDataFeature::GeoDataVisualCategory poiCategory = GeoDataFeature::OsmVisualCategory( key + '=' + value );

        //Placemark is an accepted POI
        if ( poiCategory )
        {
            // If placemark is not in the document, add it.
            if ( !placemark->parent() ) {
                placemark = createPOI( doc, geometry, osmData );
            }
            placemark->setVisible( true );
        }
    }

    if ( placemark )
    {
        GeoDataFeature::GeoDataVisualCategory category;
        if ( ( category = GeoDataFeature::OsmVisualCategory( key + '=' + value ) ) )
        {
            if( placemark->visualCategory() != GeoDataFeature::Default
             && placemark->visualCategory() != GeoDataFeature::Building )
            {
                GeoDataPlacemark* newPlacemark = new GeoDataPlacemark( *placemark );
                newPlacemark->setVisualCategory( category );
                newPlacemark->setStyle( 0 );
                newPlacemark->setVisible( true );
                doc->append( newPlacemark );
            }
            else
            {
                //Remove assigned style (i.e. building style)
                placemark->setStyle( 0 );
                placemark->setVisualCategory( category );
                placemark->setVisible( true );
            }
        }
        else if ( ( category = GeoDataFeature::OsmVisualCategory( key ) ) )
        {
            if( placemark->visualCategory() != GeoDataFeature::Default )
            {
                GeoDataPlacemark* newPlacemark = new GeoDataPlacemark( *placemark );
                newPlacemark->setVisualCategory( category );
                newPlacemark->setStyle( 0 );
                newPlacemark->setVisible( true );
                doc->append( newPlacemark );
            }
            else
            {
                //Remove assigned style (i.e. building style)
                placemark->setStyle( 0 );
                placemark->setVisualCategory( category );
                placemark->setVisible( true );
            }
        }
    }

    return 0;
}

GeoDataPlacemark* OsmTagTagHandler::createPOI( GeoDataDocument* doc, GeoDataGeometry *geometry, const OsmPlacemarkData &osmData )
{
    GeoDataPoint *point = dynamic_cast<GeoDataPoint *>( geometry );

    if ( !point ) {
        return 0;
    }
    GeoDataPlacemark *newPlacemark = new GeoDataPlacemark();
    newPlacemark->setGeometry( new GeoDataPoint( *point ) );
    newPlacemark->setOsmData( osmData );
    point->setParent( newPlacemark );
    newPlacemark->setVisible( false );
    newPlacemark->setZoomLevel( 18 );
    doc->append( newPlacemark );
    return newPlacemark;
}

}

}
