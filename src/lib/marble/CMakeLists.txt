PROJECT(marblewidget)

macro_optional_find_package(Phonon)
marble_set_package_properties( Phonon PROPERTIES DESCRIPTION "cross-platform multimedia framework that enables the use of audio and video content" )
marble_set_package_properties( Phonon PROPERTIES URL "http://qt.digia.com/" )
marble_set_package_properties( Phonon PROPERTIES TYPE OPTIONAL PURPOSE "Support for playback of soundcue elements" )

INCLUDE_DIRECTORIES(
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
 ${CMAKE_CURRENT_SOURCE_DIR}/projections
 ${CMAKE_CURRENT_SOURCE_DIR}/routing
 ${CMAKE_CURRENT_SOURCE_DIR}/geodata
 ${CMAKE_CURRENT_SOURCE_DIR}/geodata/data
 ${CMAKE_CURRENT_SOURCE_DIR}/geodata/graphicsitem
 ${CMAKE_CURRENT_SOURCE_DIR}/geodata/scene
 ${CMAKE_CURRENT_SOURCE_DIR}/geodata/handlers
 ${CMAKE_CURRENT_SOURCE_DIR}/geodata/handlers/kml
 ${CMAKE_CURRENT_SOURCE_DIR}/geodata/handlers/dgml
 ${CMAKE_CURRENT_SOURCE_DIR}/geodata/parser
 ${CMAKE_CURRENT_SOURCE_DIR}/graphicsview
 ${CMAKE_CURRENT_SOURCE_DIR}/layers
 ${CMAKE_CURRENT_SOURCE_DIR}/osm
 ${CMAKE_CURRENT_SOURCE_DIR}/cloudsync
 ${CMAKE_SOURCE_DIR}/src/lib/astro
 ${QT_INCLUDE_DIR}
)

if( QT4BUILD )
  INCLUDE(${QT_USE_FILE})
else()
INCLUDE_DIRECTORIES(
 ${Qt5WebKitWidgets_INCLUDE_DIRS}
 ${Qt5Xml_INCLUDE_DIRS}
 ${Qt5Concurrent_INCLUDE_DIRS}
 ${Qt5Quick_INCLUDE_DIRS}
)
endif()

INCLUDE(geodata/CMakeLists.txt)
INCLUDE(graphicsview/CMakeLists.txt)
INCLUDE(layers/CMakeLists.txt)
INCLUDE(osm/CMakeLists.txt)

set(GENERIC_LIB_VERSION "0.21.80")
set(GENERIC_LIB_SOVERSION "22")

# link_directories (${QT_LIBRARY_DIR})
########### next target ###############

if(MARBLE_NO_WEBKIT)
add_definitions(-DMARBLE_NO_WEBKIT)
endif()

set(marblewidget_SRCS
    ${geodata_SRCS}
    ${graphicsview_SRCS}
    ${layers_SRCS}
    ${osm_SRCS}
    blendings/Blending.cpp
    blendings/BlendingAlgorithms.cpp
    blendings/BlendingFactory.cpp
    blendings/SunLightBlending.cpp
    DownloadRegion.cpp
    DownloadRegionDialog.cpp
    LatLonBoxWidget.cpp
    MarbleWidget.cpp
    MarbleAbstractPresenter.cpp
    MarbleModel.cpp
    MarbleMap.cpp
    MarbleControlBox.cpp
    MarbleColors.cpp
    NavigationWidget.cpp
    MapViewWidget.cpp
    CelestialSortFilterProxyModel.cpp
    FileViewWidget.cpp
    TourWidget.cpp
    FlyToEditWidget.cpp
    TourControlEditWidget.cpp
    WaitEditWidget.cpp
    SoundCueEditWidget.cpp
    RemoveItemEditWidget.cpp
    TourItemDelegate.cpp
    MapViewItemDelegate.cpp
    TourPlayback.cpp
    LegendWidget.cpp
    PlaybackItem.cpp
    PlaybackAnimatedUpdateItem.cpp
    PlaybackFlyToItem.cpp
    PlaybackSoundCueItem.cpp
    PlaybackTourControlItem.cpp
    PlaybackWaitItem.cpp
    SerialTrack.cpp
    SoundTrack.cpp
    AnimatedUpdateTrack.cpp
    CurrentLocationWidget.cpp
    MarbleNavigator.cpp
    MarbleLegendBrowser.cpp
    MarbleAboutDialog.cpp
    MarbleInputHandler.cpp
    MarbleWidgetInputHandler.cpp
    MarbleWidgetPopupMenu.cpp
    MarblePlacemarkModel.cpp
    GeoDataTreeModel.cpp
    GeoUriParser.cpp
    kdescendantsproxymodel.cpp
    BranchFilterProxyModel.cpp
    TreeViewDecoratorModel.cpp
    MarbleDebug.cpp
    Tile.cpp
    TextureTile.cpp
    TileCoordsPyramid.cpp
    TileLevelRangeWidget.cpp
    TileLoader.cpp
    QtMarbleConfigDialog.cpp
    ClipPainter.cpp
    DownloadPolicy.cpp
    DownloadQueueSet.cpp
    GeoPainter.cpp
    HttpDownloadManager.cpp
    HttpJob.cpp
    RemoteIconLoader.cpp
    LayerManager.cpp
    PluginManager.cpp
    TimeControlWidget.cpp
    AbstractFloatItem.cpp
    PopupItem.cpp
    MarbleGlobal.cpp
    MarbleDirs.cpp
    MarbleLocale.cpp
    MarblePhysics.cpp
    DeferredFlag.cpp
    TileCreatorDialog.cpp
    MapThemeManager.cpp
    ViewportParams.cpp
    ViewParams.cpp
    projections/AbstractProjection.cpp
    projections/CylindricalProjection.cpp
    projections/AzimuthalProjection.cpp
    projections/SphericalProjection.cpp
    projections/EquirectProjection.cpp
    projections/MercatorProjection.cpp
    projections/GnomonicProjection.cpp
    projections/StereographicProjection.cpp
    projections/LambertAzimuthalProjection.cpp
    projections/AzimuthalEquidistantProjection.cpp
    projections/VerticalPerspectiveProjection.cpp
    VisiblePlacemark.cpp
    PlacemarkLayout.cpp
    Planet.cpp
    PlanetFactory.cpp
    Quaternion.cpp
    TextureColorizer.cpp
    TextureMapperInterface.cpp
    ScanlineTextureMapperContext.cpp
    SphericalScanlineTextureMapper.cpp
    EquirectScanlineTextureMapper.cpp
    MercatorScanlineTextureMapper.cpp
    TileScalingTextureMapper.cpp
    GenericScanlineTextureMapper.cpp
    VectorTileModel.cpp
    DiscCache.cpp
    ServerLayout.cpp
    StoragePolicy.cpp
    CacheStoragePolicy.cpp
    FileStoragePolicy.cpp
    FileStorageWatcher.cpp
    StackedTile.cpp
    TileId.cpp
    StackedTileLoader.cpp
    TileLoaderHelper.cpp
    TileCreator.cpp
    #jsonparser.cpp
    FileLoader.cpp
    FileManager.cpp
    PositionTracking.cpp
    DataMigration.cpp
    ImageF.cpp
    MovieCapture.cpp
    MovieCaptureDialog.cpp
    TourCaptureDialog.cpp
    EditPlacemarkDialog.cpp
    AddLinkDialog.cpp
    FormattedTextWidget.cpp

    AbstractDataPlugin.cpp
    AbstractDataPluginModel.cpp
    AbstractDataPluginItem.cpp
    AbstractWorkerThread.cpp

    PluginInterface.cpp
    DialogConfigurationInterface.cpp
    LayerInterface.cpp
    RenderState.cpp
    RenderPlugin.cpp
    RenderPluginInterface.cpp
    PositionProviderPlugin.cpp
    PositionProviderPluginInterface.cpp
    PlacemarkPositionProviderPlugin.cpp
    RouteSimulationPositionProviderPlugin.cpp
    MarblePluginSettingsWidget.cpp
    RenderPluginModel.cpp
    PluginAboutDialog.cpp
    PluginItemDelegate.cpp

    SunLocator.cpp
    MarbleClock.cpp
    SunControlWidget.cpp
    MergedLayerDecorator.cpp

    MathHelper.cpp

    LatLonEdit.cpp
    PlacemarkEditHeader.cpp

    MapThemeSortFilterProxyModel.cpp

    TemplateDocument.cpp

    routing/AlternativeRoutesModel.cpp
    routing/Maneuver.cpp
    routing/Route.cpp
    routing/RouteRequest.cpp
    routing/RouteSegment.cpp
    routing/RoutingModel.cpp
    routing/RoutingProfile.cpp
    routing/RoutingManager.cpp
    routing/RoutingLayer.cpp
    routing/RoutingInputWidget.cpp
    routing/RoutingWidget.cpp
    routing/RoutingProfilesWidget.cpp
    routing/RoutingProfilesModel.cpp
    routing/RoutingProfileSettingsDialog.cpp
    routing/SpeakersModel.cpp
    routing/VoiceNavigationModel.cpp
    routing/instructions/InstructionTransformation.cpp
    routing/instructions/RoutingInstruction.cpp
    routing/instructions/RoutingPoint.cpp
    routing/instructions/RoutingWaypoint.cpp
    routing/instructions/WaypointParser.cpp

    ParsingRunnerManager.cpp
    ReverseGeocodingRunnerManager.cpp
    RoutingRunnerManager.cpp
    SearchRunnerManager.cpp

    AutoNavigation.cpp

    SearchRunnerPlugin.cpp
    ReverseGeocodingRunnerPlugin.cpp
    RoutingRunnerPlugin.cpp
    ParseRunnerPlugin.cpp
    SearchRunner.cpp
    ReverseGeocodingRunner.cpp
    RoutingRunner.cpp
    ParsingRunner.cpp
    RunnerTask.cpp

    BookmarkManager.cpp
    EditBookmarkDialog.cpp
    BookmarkManagerDialog.cpp
    NewBookmarkFolderDialog.cpp

    PrintOptionsWidget.cpp
    ExternalEditorDialog.cpp
    GoToDialog.cpp

    MapWizard.cpp
    MapThemeDownloadDialog.cpp
    GeoGraphicsScene.cpp
    ElevationModel.cpp
    MarbleLineEdit.cpp
    SearchInputWidget.cpp
    SearchWidget.cpp
    kineticmodel.cpp
    NewstuffModel.cpp
    
    cloudsync/CloudSyncManager.cpp
    cloudsync/RouteSyncManager.cpp
    cloudsync/OwncloudSyncBackend.cpp
    cloudsync/CloudRouteModel.cpp
    cloudsync/CloudRoutesDialog.cpp
    cloudsync/RouteItem.cpp
    cloudsync/RouteItemDelegate.cpp
    cloudsync/BookmarkSyncManager.cpp
    cloudsync/MergeItem.cpp
    cloudsync/ConflictDialog.cpp
)


if (MARBLE_NO_WEBKIT)
    LIST(APPEND marblewidget_SRCS
        NullMarbleWebView.cpp
        NullTinyWebBrowser.cpp
        )
else()
    LIST(APPEND marblewidget_SRCS
        MarbleWebView.cpp
        TinyWebBrowser.cpp
        )
endif()

if (NOT QT_NO_DBUS)
    LIST(APPEND marblewidget_SRCS
        MarbleDBusInterface.cpp
        )
endif()

set (marblewidget_UI
    LatLonBoxWidget.ui
    NavigationWidget.ui
    MapViewWidget.ui
    CurrentLocationWidget.ui
    FileViewWidget.ui
    TourWidget.ui
    MarbleNavigator.ui
    MarbleCacheSettingsWidget.ui
    MarbleViewSettingsWidget.ui
    MarbleNavigationSettingsWidget.ui
    TimeControlWidget.ui
    MarbleTimeSettingsWidget.ui
    MarblePluginSettingsWidget.ui
    TileCreatorDialog.ui
    TileLevelRangeWidget.ui
    MarbleAboutDialog.ui
    SunControlWidget.ui
    LatLonEdit.ui
    PlacemarkEditHeader.ui
    routing/RoutingWidget.ui
    DataMigrationWidget.ui
    EditBookmarkDialog.ui
    BookmarkManagerDialog.ui
    NewBookmarkFolderDialog.ui
    PrintOptions.ui
    ExternalEditor.ui
    GoToDialog.ui
    routing/RoutingSettingsWidget.ui
    routing/RoutingProfileSettingsDialog.ui
    MapWizard.ui
    MapThemeDownloadDialog.ui
    cloudsync/CloudRoutesDialog.ui
    MarbleCloudSyncSettingsWidget.ui
    MovieCaptureDialog.ui
    TourCaptureDialog.ui
    EditPlacemarkDialog.ui
    AddLinkDialog.ui
    FormattedTextWidget.ui
    ElevationWidget.ui
)
if (MARBLE_NO_WEBKIT)
    LIST(APPEND marblewidget_UI
        NullLegendWidget.ui
        NullWebPopupWidget.ui
        )
else()
    LIST(APPEND marblewidget_UI
        LegendWidget.ui
        WebPopupWidget.ui
        )
endif()

# FIXME: cleaner approach of src/lib/marblwidget/MarbleControlBox.* vs. marble.qrc
qt_add_resources(marblewidget_SRCS libmarble.qrc ../../apps/marble-ui/marble.qrc)

qt_wrap_ui(marblewidget_SRCS ${marblewidget_UI})

ADD_LIBRARY(${MARBLEWIDGET} SHARED ${marblewidget_SRCS} ${SOURCES_UI_HDRS})

# link with libastro
TARGET_LINK_LIBRARIES (${MARBLEWIDGET} astro)

# link with release version of Qt libs
if( QT4BUILD )
  TARGET_LINK_LIBRARIES (${MARBLEWIDGET}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTDBUS_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTXML_LIBRARY}
    ${QT_QTSVG_LIBRARY}
    ${QT_QTNETWORK_LIBRARY}
    ${QT_QTSCRIPT_LIBRARY}
    ${QT_QTMAIN_LIBRARY}
    ${QT_QTWEBKIT_LIBRARY}
    ${QT_QTDECLARATIVE_LIBRARY}
  )
else()
  TARGET_LINK_LIBRARIES (${MARBLEWIDGET}
    ${Qt5Core_LIBRARIES}
    ${Qt5Xml_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5WebKitWidgets_LIBRARIES}
    ${Qt5Svg_LIBRARIES}
    ${Qt5Script_LIBRARIES}
    ${Qt5Quick_LIBRARIES}
    ${Qt5OpenGL_LIBRARIES}
    ${Qt5PrintSupport_LIBRARIES}
    ${Qt5DBus_LIBRARIES}
    )
endif()

if( PHONON_FOUND AND NOT QT5BUILD )
  INCLUDE_DIRECTORIES( ${PHONON_INCLUDES} )
  TARGET_LINK_LIBRARIES(${MARBLEWIDGET} ${PHONON_LIBS} )
  set (HAVE_PHONON TRUE)
endif( PHONON_FOUND AND NOT QT5BUILD )

if (APPLE)
  #defined in top level makefile
  TARGET_LINK_LIBRARIES(${MARBLEWIDGET} ${MAC_EXTRA_LIBS} )
endif (APPLE)

if (CMAKE_SYSTEM_NAME MATCHES "SunOS")
  TARGET_LINK_LIBRARIES(${MARBLEWIDGET} m)
endif (CMAKE_SYSTEM_NAME MATCHES "SunOS")

if(WIN32)
  TARGET_LINK_LIBRARIES(${MARBLEWIDGET} ws2_32 imm32 winmm)
endif(WIN32)


set_target_properties(${MARBLEWIDGET}  PROPERTIES
                                    VERSION ${GENERIC_LIB_VERSION}
                                    SOVERSION ${GENERIC_LIB_SOVERSION}
                                    COMPILE_FLAGS "-DKML_LAZY_IMP")
# needed for marble_export.h
set_target_properties(${MARBLEWIDGET} PROPERTIES
  DEFINE_SYMBOL MAKE_MARBLE_LIB
)

# choose the correct target install library path
if(WIN32)
  install(TARGETS ${MARBLEWIDGET} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
elseif(APPLE)
  install(TARGETS ${MARBLEWIDGET} LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/Marble.app/Contents/MacOS/lib)
else()
  install(TARGETS ${MARBLEWIDGET} LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})
endif()


########### install files ###############

if (MARBLE_NO_WEBKIT)
    set(marble_WebKit
        NullMarbleWebView.h
        NullTinyWebBrowser.h
        )
else()
    set(marble_WebKit
        MarbleWebView.h
        TinyWebBrowser.h
        )
endif()

install( FILES
    ${graphicsview_HDRS}
    ${marble_WebKit}
    AutoNavigation.h
    BookmarkManager.h
    DownloadRegion.h
    DownloadRegionDialog.h
    LatLonBoxWidget.h
    MarbleWidget.h
    MarbleMap.h
    MarbleModel.h
    MarbleControlBox.h
    NavigationWidget.h
    MapViewWidget.h
    CelestialSortFilterProxyModel.h
    LegendWidget.h
    FileViewWidget.h
    TourWidget.h
    FlyToEditWidget.h
    TourControlEditWidget.h
    WaitEditWidget.h
    SoundCueEditWidget.h
    RemoveItemEditWidget.h
    TourItemDelegate.h
    MapViewItemDelegate.h
    TourPlayback.h
    CurrentLocationWidget.h
    MarbleNavigator.h
    AbstractFloatItem.h
    MapThemeManager.h
    MarbleAboutDialog.h
    MarbleInputHandler.h
    MarbleWidgetInputHandler.h
    MarbleWidgetPopupMenu.h
    TileId.h
    TileCoordsPyramid.h
    TileLevelRangeWidget.h
    QtMarbleConfigDialog.h
    global.h
    MarbleColors.h
    MarbleGlobal.h
    MarbleLocale.h
    MarbleDebug.h
    MarbleDirs.h
    GeoPainter.h
    HttpDownloadManager.h
    TileCreatorDialog.h
    ViewportParams.h
    projections/AbstractProjection.h
    PositionTracking.h
    Quaternion.h
    SunLocator.h
    ClipPainter.h
    GeoGraphicsScene.h
    GeoDataTreeModel.h
    geodata/data/GeoDataAbstractView.h
    geodata/data/GeoDataAccuracy.h
    geodata/data/GeoDataBalloonStyle.h
    geodata/data/GeoDataColorStyle.h
    geodata/data/GeoDataContainer.h
    geodata/data/GeoDataCoordinates.h
    geodata/data/GeoDataDocument.h
    geodata/data/GeoDataFeature.h
    geodata/data/GeoDataFolder.h
    geodata/data/GeoDataGeometry.h
    geodata/data/GeoDataGroundOverlay.h
    geodata/data/GeoDataHotSpot.h
    geodata/data/GeoDataIconStyle.h
    geodata/data/GeoDataItemIcon.h
    geodata/data/GeoDataLabelStyle.h
    geodata/data/GeoDataLatLonAltBox.h
    geodata/data/GeoDataLatLonBox.h
    geodata/data/GeoDataLatLonQuad.h
    geodata/data/GeoDataLinearRing.h
    geodata/data/GeoDataLineString.h
    geodata/data/GeoDataLineStyle.h
    geodata/data/GeoDataListStyle.h
    geodata/data/GeoDataLod.h
    geodata/data/GeoDataLookAt.h
    geodata/data/GeoDataOverlay.h
    geodata/data/GeoDataMultiGeometry.h
    geodata/data/GeoDataObject.h
    geodata/data/GeoDataPlacemark.h
    geodata/data/GeoDataPoint.h
    geodata/data/GeoDataPolygon.h
    geodata/data/GeoDataPolyStyle.h
    geodata/data/GeoDataRegion.h
    geodata/data/GeoDataSnippet.h
    geodata/data/GeoDataStyle.h
    geodata/data/GeoDataStyleMap.h
    geodata/data/GeoDataStyleSelector.h
    geodata/data/GeoDataTrack.h
    geodata/data/GeoDataTimeSpan.h
    geodata/data/GeoDataTimeStamp.h
    geodata/data/GeoDataTimePrimitive.h
    geodata/data/Serializable.h
    geodata/geodata_export.h
    geodata/parser/GeoDocument.h
    geodata/writer/GeoWriter.h
    routing/RoutingWidget.h
    routing/RoutingManager.h
    TileCreator.h
    PluginManager.h
    PluginInterface.h
    DialogConfigurationInterface.h
    PositionProviderPlugin.h
    PositionProviderPluginInterface.h
    RenderPlugin.h
    RenderPluginInterface.h
    ParsingRunnerManager.h
    ReverseGeocodingRunnerManager.h
    RoutingRunnerManager.h
    SearchRunnerManager.h
    ParsingRunner.h
    SearchRunner.h
    ReverseGeocodingRunner.h
    RoutingRunner.h
    SearchRunnerPlugin.h
    ReverseGeocodingRunnerPlugin.h
    RoutingRunnerPlugin.h
    ParseRunnerPlugin.h
    LayerInterface.h
    RenderState.h
    PluginAboutDialog.h
    marble_export.h
    Planet.h
    PlanetFactory.h
    EditPlacemarkDialog.h
    AddLinkDialog.h
    FormattedTextWidget.h

    AbstractDataPlugin.h
    AbstractDataPluginModel.h
    AbstractDataPluginItem.h
    AbstractWorkerThread.h

    LatLonEdit.h
    PlacemarkEditHeader.h
    MapWizard.h
    MapThemeDownloadDialog.h
    ElevationModel.h

    routing/AlternativeRoutesModel.h
    routing/Route.h
    routing/Maneuver.h
    routing/RouteRequest.h
    routing/RouteSegment.h
    routing/RoutingManager.h
    routing/RoutingModel.h
    routing/RoutingProfile.h

    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/marble
)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config-phonon.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/config-phonon.h)
