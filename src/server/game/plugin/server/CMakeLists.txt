set(ProjectName "game_server_net_server_plugin")
file(GLOB GameServerNet_ServerPlugin_ROOT_Cpp
	*.cc)
	
file(GLOB GameServerNet_ServerPlugin_ROOT_Hpp 
	*.h)

add_library(game_server_net_server_plugin SHARED
	${GameServerNet_ServerPlugin_ROOT_Cpp}
	${GameServerNet_ServerPlugin_ROOT_Hpp})
	
set_target_properties( game_server_net_server_plugin PROPERTIES OUTPUT_NAME "server")
set_target_properties( game_server_net_server_plugin PROPERTIES PREFIX "")
set_target_properties( game_server_net_server_plugin PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/game
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/game
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/game )

add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
