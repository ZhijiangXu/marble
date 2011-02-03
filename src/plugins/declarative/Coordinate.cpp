//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2011      Dennis Nienhüser <earthwings@gentoo.org>
//

#include "Coordinate.h"

#include "MarbleMath.h"

namespace Marble
{
namespace Declarative
{

Coordinate::Coordinate( qreal lon, qreal lat, qreal alt, QObject *parent ) :
    QObject( parent )
{
    setLongitude( lon );
    setLatitude( lat );
    setAltitude( alt );
}

qreal Coordinate::longitude() const
{
    return m_coordinate.longitude( GeoDataCoordinates::Degree );
}

void Coordinate::setLongitude( qreal lon )
{
    m_coordinate.setLongitude( lon, GeoDataCoordinates::Degree );
    emit longitudeChanged();
}

qreal Coordinate::latitude() const
{
    return m_coordinate.latitude( GeoDataCoordinates::Degree );
}

void Coordinate::setLatitude( qreal lat )
{
    m_coordinate.setLatitude( lat, GeoDataCoordinates::Degree );
    emit latitudeChanged();
}

qreal Coordinate::altitude() const
{
    return m_coordinate.altitude();
}

void Coordinate::setAltitude( qreal alt )
{
    m_coordinate.setAltitude( alt );
    emit altitudeChanged();
}

GeoDataCoordinates Coordinate::coordinates() const
{
    return m_coordinate;
}

void Coordinate::setCoordinates( const GeoDataCoordinates &coordinates )
{
    m_coordinate = coordinates;
}

qreal Coordinate::distance( qreal longitude, qreal latitude ) const
{
    GeoDataCoordinates::Unit deg = GeoDataCoordinates::Degree;
    GeoDataCoordinates other( longitude, latitude, 0, deg );
    return EARTH_RADIUS * distanceSphere( coordinates(), other );
}

}
}

#include "Coordinate.moc"
