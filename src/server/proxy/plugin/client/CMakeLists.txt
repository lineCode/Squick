set(ProjectName "proxy_server_net_client_plugin")
file(GLOB ProxyServerNet_ClientPlugin_ROOT_Cpp
	*.cc)

file(GLOB ProxyServerNet_ClientPlugin_ROOT_Hpp 
	*.h)

add_library(proxy_server_net_client_plugin SHARED
	${ProxyServerNet_ClientPlugin_ROOT_Cpp}
	${ProxyServerNet_ClientPlugin_ROOT_Hpp})
	
set_target_properties( proxy_server_net_client_plugin PROPERTIES OUTPUT_NAME "client")
set_target_properties( proxy_server_net_client_plugin PROPERTIES PREFIX "")
set_target_properties( proxy_server_net_client_plugin PROPERTIES 
	FOLDER "server/plugin/proxy_server_net_client"
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/proxy
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/proxy
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/proxy )

target_link_libraries(proxy_server_net_client_plugin -static-libstdc++)
add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)
