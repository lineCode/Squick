set(ProjectName "plugin_loader")
file(GLOB PluginLoader_ROOT_Cpp *.cc)
file(GLOB PluginLoader_ROOT_Hpp *.h)

add_library(squick_plugin_loader SHARED
		${PluginLoader_ROOT_Cpp}
		${PluginLoader_ROOT_Hpp})

target_link_libraries(squick_plugin_loader -static-libstdc++ -pthread ${CMAKE_DL_LIBS})

set_target_properties( squick_plugin_loader PROPERTIES OUTPUT_NAME "squick_plugin_loader")
set_target_properties( squick_plugin_loader PROPERTIES PREFIX "")
set_target_properties( squick_plugin_loader PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH} )

add_definitions(-D_X64 -D_CONSOLE)