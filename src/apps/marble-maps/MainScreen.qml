//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2015      Gábor Péterffy <peterffy95@gmail.com>
// Copyright 2015      Dennis Nienhüser <nienhueser@kde.org>
// Copyright 2015      Mikhail Ivchenko <ematirov@gmail.com>
//


import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

import org.kde.edu.marble 0.20

ApplicationWindow {
    id: root
    title: qsTr("Marble Maps")
    visible: true

    menuBar: MenuBar {
        id: menuBar
        Menu {
            title: qsTr("Marble Maps")
            MenuItem{
                text: qsTr("Search")
                onTriggered: search.visible = !search.visible
            }

            MenuItem {
                text: qsTr("Delete Route")
                onTriggered: {routing.clearRoute(); instructions.visible = false; startRoutingButton.show = false; waypointOrderEditor.visible = false;}
                visible: routing.hasRoute
            }

            MenuItem {
                text: waypointOrderEditor.visible ? qsTr("Hide Route Modifier") : qsTr("Modify Route")
                onTriggered: {waypointOrderEditor.visible = !waypointOrderEditor.visible; instructions.visible = false}
                visible: routing.hasRoute
            }

            MenuItem {
                text: qsTr("Navigation Instructions")
                onTriggered: {instructions.visible = true}
                visible: routing.hasRoute && !instructions.visible
            }

            MenuItem {
                text: qsTr("Show the Map")
                onTriggered: {instructions.visible = false}
                visible: instructions.visible
            }
        }
    }

    toolBar: ToolBar {
        id: toolBar
    }

    width: 600
    height: 400

    SystemPalette{
        id: palette
        colorGroup: SystemPalette.Active
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: palette.window
    }

    PinchArea {
        anchors.fill: parent
        enabled: true

        onPinchStarted: marbleMaps.handlePinchStarted(pinch.center)
        onPinchFinished: marbleMaps.handlePinchFinished(pinch.center)
        onPinchUpdated: marbleMaps.handlePinchUpdated(pinch.center, pinch.scale);

        MarbleMaps {
            id: marbleMaps

            anchors.fill: parent
            visible: true
            focus: true

            // Theme settings.
            projection: MarbleItem.Mercator
            mapThemeId: "earth/openstreetmap/openstreetmap.dgml"

            // Visibility of layers/plugins.
            showFrameRate: false
            showAtmosphere: false
            showCompass: false
            showClouds: false
            showCrosshairs: false
            showGrid: false
            showOverviewMap: false
            showOtherPlaces: false
            showScaleBar: false
            showBackground: false
            positionProvider: suspended ? "" : "QtPositioning"
            showPositionMarker: true

            onPositionAvailableChanged: updateIndicator()
            onPositionVisibleChanged: updateIndicator()
            onViewportChanged: updateIndicator()

            function updateIndicator() {
                if ( !positionVisible && positionAvailable ) {
                    zoomToPositionButton.updateIndicator();
                }
            }

            RoutingManager {
                id: routing
                anchors.fill: parent
                marbleItem: marbleMaps
                navigationSetup: navigationSettings
                selectedPlacemark: search.searchResultPlacemark
                routingProfile: profileChoosingMenu.selectedProfile
            }
        }

        MouseArea{
            anchors.fill: parent
            propagateComposedEvents: true
            onPressed: {
                search.focus = true;
                mouse.accepted = false;
            }
        }
    }

    PositionButton {
        id: zoomToPositionButton
        anchors {
            bottom: parent.bottom
            right: parent.right
            bottomMargin: startRoutingButton.height
            rightMargin: 0.005 * root.width
        }

        iconSource: marbleMaps.positionAvailable ? "qrc:///gps_fixed.png" : "qrc:///gps_not_fixed.png"

        onClicked: marbleMaps.centerOnCurrentPosition()

        property real distance: 0

        function updateIndicator() {
            var point = marbleMaps.mapFromItem(zoomToPositionButton, diameter * 0.5, diameter * 0.5);
            distance = 0.001 * marbleMaps.distanceFromPointToCurrentLocation(point);
            angle = marbleMaps.angleFromPointToCurrentLocation(point);
        }

        showDirection: marbleMaps.positionAvailable && !marbleMaps.positionVisible
    }

    BoxedText {
        id: distanceIndicator
        text: "%1 km".arg(zoomToPositionButton.distance < 10 ? zoomToPositionButton.distance.toFixed(1) : zoomToPositionButton.distance.toFixed(0))
        anchors {
            bottom: zoomToPositionButton.top
            horizontalCenter: zoomToPositionButton.horizontalCenter
        }

        visible: marbleMaps.positionAvailable && !marbleMaps.positionVisible
    }

    Search {
        id: search
        anchors.fill: parent
        marbleQuickItem: marbleMaps
        onItemSelected: { startRoutingButton.show = true; startRoutingButton.navigation = false; }
    }

    CircularButton {
        id: startRoutingButton

        property bool navigation: false
        property bool show: false

        visible: show || routing.hasRoute

        anchors {
            bottom: changeProfileButton.top
            horizontalCenter: changeProfileButton.horizontalCenter
        }

        iconSource: navigation ? "qrc:///navigation.png" : "qrc:///map.png"

        onClicked: {
            if (navigation) {
                routing.addPositionAsDeparture();
            }
            else {
                navigationSettings.visible = true;
                navigation = true;
            }
        }
    }

    CircularButton {
        id: changeProfileButton
        visible: routing.hasRoute && !search.searchResultsVisible
        anchors {
            bottom: distanceIndicator.top
            horizontalCenter: zoomToPositionButton.horizontalCenter
            margins: 0.01 * root.width
        }

        iconSource: routing.profileIcon
        onClicked: { profileChoosingMenu.focus = true; }
    }

    ProfileSelectorMenu {
        id: profileChoosingMenu
        visible: focus
        anchors {
            right: changeProfileButton.right
            verticalCenter: changeProfileButton.verticalCenter
        }
    }

    NavigationSetup {
        id: navigationSettings
        visible: false
        property bool departureIsSet: false
        property bool destinationIsSet: false

        height: Screen.pixelDensity * 9
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
    }

    WaypointOrderManager {
        id: waypointOrderEditor
        anchors.fill: parent
        visible: false
        routingManager:routing
    }

    RoutePlanViewer{
        id: instructions
        visible: false
        anchors.fill: parent
        model: routing.routingModel
    }
}
