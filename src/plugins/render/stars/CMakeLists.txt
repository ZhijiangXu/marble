PROJECT( StarsPlugin )

INCLUDE_DIRECTORIES(
 ${CMAKE_SOURCE_DIR}/src/lib/astro
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
 ${QT_INCLUDE_DIR}
)
if( QT4BUILD )
  INCLUDE(${QT_USE_FILE})
endif()

set( stars_SRCS StarsPlugin.cpp )
set( stars_UI StarsConfigWidget.ui )

qt_wrap_ui(stars_SRCS  ${stars_UI})

marble_add_plugin( StarsPlugin ${stars_SRCS} )
target_link_libraries( StarsPlugin astro )
