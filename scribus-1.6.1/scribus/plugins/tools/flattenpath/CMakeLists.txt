include_directories(
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/scribus
)

set(FLATTENPATH_PLUGIN_SOURCES
	flattenpath.cpp
)

set(SCRIBUS_FLATTENPATH_PLUGIN "flattenpath")

add_library(${SCRIBUS_FLATTENPATH_PLUGIN} MODULE ${FLATTENPATH_PLUGIN_SOURCES})

target_link_libraries(${SCRIBUS_FLATTENPATH_PLUGIN} ${EXE_NAME})

if(WANT_PCH)
	target_precompile_headers(${SCRIBUS_FLATTENPATH_PLUGIN} PRIVATE "../../plugins_pch.h")
endif()

install(TARGETS ${SCRIBUS_FLATTENPATH_PLUGIN}
	LIBRARY
	DESTINATION ${PLUGINDIR}
	PERMISSIONS ${PLUGIN_PERMISSIONS}
)
