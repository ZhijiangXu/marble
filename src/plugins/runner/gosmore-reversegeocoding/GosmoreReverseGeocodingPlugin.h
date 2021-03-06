//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2010      Dennis Nienhüser <nienhueser@kde.org>
// Copyright 2012      Bernhard Beschow <bbeschow@cs.tu-berlin.de>
//


#ifndef MARBLE_GOSMOREREVERSEGEOCODINGPLUGIN_H
#define MARBLE_GOSMOREREVERSEGEOCODINGPLUGIN_H

#include "ReverseGeocodingRunnerPlugin.h"

namespace Marble
{

class GosmorePlugin : public ReverseGeocodingRunnerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA( IID "org.kde.edu.marble.GosmoreReverseGeocodingPlugin" )
    Q_INTERFACES( Marble::ReverseGeocodingRunnerPlugin )

public:
    explicit GosmorePlugin( QObject *parent = 0 );

    QString name() const;

    QString guiString() const;

    QString nameId() const;

    QString version() const;

    QString description() const;

    QString copyrightYears() const;

    QList<PluginAuthor> pluginAuthors() const;

    virtual ReverseGeocodingRunner* newRunner() const;

    virtual bool canWork() const;
};

}

#endif
