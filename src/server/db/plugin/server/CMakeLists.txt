set(ProjectName "db_net_server_plugin")
file(GLOB DBNet_ServerPlugin_ROOT_Cpp
	*.cc)

file(GLOB DBNet_ServerPlugin_ROOT_Hpp 
	*.h)

add_library(db_net_server_plugin SHARED
	${DBNet_ServerPlugin_ROOT_Cpp}
	${DBNet_ServerPlugin_ROOT_Hpp})
	
set_target_properties( db_net_server_plugin PROPERTIES OUTPUT_NAME "server")
set_target_properties( db_net_server_plugin PROPERTIES PREFIX "")
set_target_properties( db_net_server_plugin PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db )

add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
