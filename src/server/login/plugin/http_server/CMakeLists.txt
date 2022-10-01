set(ProjectName "login_net_http_server_plugin")
file(GLOB LoginNet_HttpServerPlugin_ROOT_Cpp *.cc)
file(GLOB LoginNet_HttpServerPlugin_ROOT_Hpp *.h)

add_library(login_net_http_server_plugin SHARED
	${LoginNet_HttpServerPlugin_ROOT_Cpp}
	${LoginNet_HttpServerPlugin_ROOT_Hpp})
	
set_target_properties( login_net_http_server_plugin PROPERTIES OUTPUT_NAME "http_server")
set_target_properties( login_net_http_server_plugin PROPERTIES PREFIX "")
set_target_properties( login_net_http_server_plugin PROPERTIES 
ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/login
RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/login
LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/login )


add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
