set(ProjectName "login_net_client_plugin")
file(GLOB LoginNet_ClientPlugin_ROOT_Cpp
	*.cc)

file(GLOB LoginNet_ClientPlugin_ROOT_Hpp 
	*.h)

add_library(login_net_client_plugin SHARED
	${LoginNet_ClientPlugin_ROOT_Cpp}
	${LoginNet_ClientPlugin_ROOT_Hpp})
	
set_target_properties( login_net_client_plugin PROPERTIES OUTPUT_NAME "client")
set_target_properties( login_net_client_plugin PROPERTIES PREFIX "")
set_target_properties( login_net_client_plugin PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/login
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/login
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/login )


add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
