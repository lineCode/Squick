set(ProjectName "world_net_server_plugin")
file(GLOB WorldNet_ServerPlugin_ROOT_Cpp
	*.cc)

file(GLOB WorldNet_ServerPlugin_ROOT_Hpp 
	*.h)

add_library(world_net_server_plugin SHARED
	${WorldNet_ServerPlugin_ROOT_Cpp}
	${WorldNet_ServerPlugin_ROOT_Hpp})
	
set_target_properties( world_net_server_plugin PROPERTIES OUTPUT_NAME "server")
set_target_properties( world_net_server_plugin PROPERTIES PREFIX "")
set_target_properties( world_net_server_plugin PROPERTIES 
	FOLDER "server/plugin/world_net_server_plugin"
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/world
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/world
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/world )



target_link_libraries(world_net_server_plugin -static-libstdc++)
add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)

