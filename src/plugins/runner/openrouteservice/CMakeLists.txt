PROJECT( OpenRouteServicePlugin )

INCLUDE_DIRECTORIES(
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
 ${QT_INCLUDE_DIR}
)
if( QT4BUILD )
  INCLUDE(${QT_USE_FILE})
else()
INCLUDE_DIRECTORIES(
  ${Qt5WebKitWidgets_INCLUDE_DIRS}
  ${Qt5Xml_INCLUDE_DIRS}
)
endif()

set( openrouteservice_SRCS OpenRouteServiceRunner.cpp OpenRouteServicePlugin.cpp )

set( openrouteservice_UI OpenRouteServiceConfigWidget.ui )

qt_wrap_ui( openrouteservice_SRCS ${openrouteservice_UI} )

marble_add_plugin( OpenRouteServicePlugin ${openrouteservice_SRCS} )
