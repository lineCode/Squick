set(ProjectName "plugin_game_server_net_client")
file(GLOB GameServerNet_ClientPlugin_ROOT_Cpp
	*.cc)
	
file(GLOB GameServerNet_ClientPlugin_ROOT_Hpp 
	*.h)

add_library(plugin_game_server_net_client SHARED
	${GameServerNet_ClientPlugin_ROOT_Cpp}
	${GameServerNet_ClientPlugin_ROOT_Hpp})
	
set_target_properties( plugin_game_server_net_client PROPERTIES OUTPUT_NAME "client")
set_target_properties( plugin_game_server_net_client PROPERTIES PREFIX "")
set_target_properties( plugin_game_server_net_client PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/game
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/game
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/game )

add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
