set(ProjectName "master_server_plugin")
file(GLOB MasterServerPlugin_ROOT_Cpp
	*.cc)

file(GLOB MasterServerPlugin_ROOT_Hpp 
	*.h)

add_library(master_server_plugin SHARED
	${MasterServerPlugin_ROOT_Cpp}
	${MasterServerPlugin_ROOT_Hpp})
	
set_target_properties( master_server_plugin PROPERTIES OUTPUT_NAME "logic")
set_target_properties( master_server_plugin PROPERTIES PREFIX "")
set_target_properties( master_server_plugin PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/master
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/master
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/master )


add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)

