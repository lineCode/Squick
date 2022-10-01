set(ProjectName "master_net_server_plugin")
file(GLOB MasterNet_ServerPlugin_ROOT_Cpp
	*.cc)

file(GLOB MasterNet_ServerPlugin_ROOT_Hpp 
	*.h)

add_library(master_net_server_plugin SHARED
	${MasterNet_ServerPlugin_ROOT_Cpp}
	${MasterNet_ServerPlugin_ROOT_Hpp})
	
set_target_properties( master_net_server_plugin PROPERTIES OUTPUT_NAME "server")
set_target_properties( master_net_server_plugin PROPERTIES PREFIX "")
set_target_properties( master_net_server_plugin PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/master
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/master
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/master )


add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)
