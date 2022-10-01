set(ProjectName "db_net_client_plugin")
file(GLOB Net_ClientPlugin_ROOT_Cpp
	*.cc)

file(GLOB Net_ClientPlugin_ROOT_Hpp 
	*.h)

add_library(db_net_client_plugin SHARED
	${Net_ClientPlugin_ROOT_Cpp}
	${Net_ClientPlugin_ROOT_Hpp})
	
set_target_properties( db_net_client_plugin PROPERTIES OUTPUT_NAME "client")
set_target_properties( db_net_client_plugin PROPERTIES PREFIX "")
set_target_properties( db_net_client_plugin PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db )

add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)