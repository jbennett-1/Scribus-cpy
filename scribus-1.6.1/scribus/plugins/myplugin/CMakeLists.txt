include_directories(
${CMAKE_SOURCE_DIR}
${CMAKE_SOURCE_DIR}/scribus
)

set(MY_PLUGIN_MOC_CLASSES
myplugin.h
mypluginimpl.h
)

set(MY_PLUGIN_SOURCES
myplugin.cpp
mypluginimpl.cpp
)

set(SCRIBUS_MY_PLUGIN "myplugin")

QT5_WRAP_CPP(MY_PLUGIN_MOC_SOURCES ${MY_PLUGIN_MOC_CLASSES})

add_library(${SCRIBUS_MY_PLUGIN} MODULE ${MY_PLUGIN_SOURCES} ${MY_PLUGIN_MOC_SOURCES})

target_link_libraries(${SCRIBUS_MY_PLUGIN} ${EXE_NAME})

if(WANT_PCH)
	target_precompile_headers(${SCRIBUS_MY_PLUGIN} PRIVATE "../plugins_pch.h")
endif()

install(TARGETS ${SCRIBUS_MY_PLUGIN}
  LIBRARY
  DESTINATION ${PLUGINDIR}
  PERMISSIONS ${PLUGIN_PERMISSIONS}
)

# set_target_properties(${SCRIBUS_FONTPREVIEW_PLUGIN} PROPERTIES VERSION "0.0.0")
