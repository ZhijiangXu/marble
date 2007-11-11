//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2007      Murad Tagirov <tmurad@gmail.com>
// Copyright 2007      Inge Wallin   <inge@lysator.liu.se>
//


#ifndef GEODATACONTAINER_H
#define GEODATACONTAINER_H

#include <QtCore/QVector>

#include "GeoDataFeature.h"

class ViewParams;

/**
 * @short  A base class that can hold GeoDataFeatures
 *
 * GeoDataContainer is the base class for the GeoData container
 * classes GeoDataFolder and GeoDataDocument.  It is never
 * instantiated by itself, but is always used as part of a derived
 * class.
 *
 * It is based on GeoDataFeature, and it only adds a
 * QVector<GeodataFeature *> to it, making it a Feature that can hold
 * other Features.
 *
 * @see GeoDataFolder
 * @see GeoDataDocument
 */
class GeoDataContainer : public GeoDataFeature
{
 public:
    /// Destruct the GeoDataContainer
    virtual ~GeoDataContainer();

    void addFeature( GeoDataFeature* feature );

    virtual void pack( QDataStream& stream ) const;
    virtual void unpack( QDataStream& stream );

#if 0
    /*
     * Will move this method to GeoDataDocumentModel in a next step
     */
    PlaceMarkContainer& activePlaceMarkContainer( const ViewParams& viewParams );
#endif

 protected:
    GeoDataContainer();
    QVector < GeoDataFeature* >  m_featureVector;

 private:
#if 0  // FIXME: This doesn't belong here.
    PlaceMarkContainer& sphericalActivePlaceMarkContainer( const ViewParams& viewParams );
    PlaceMarkContainer& rectangularActivePlaceMarkContainer( const ViewParams& viewParams );

    PlaceMarkContainer m_activePlaceMarkContainer;
#endif
};

#endif // GEODATACONTAINER_H
