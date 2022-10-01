set(ProjectName "proxy_logic_plugin")
file(GLOB ProxyLogicPlugin_ROOT_Cpp
	*.cc)

file(GLOB ProxyLogicPlugin_ROOT_Hpp 
	*.h)

add_library(proxy_logic_plugin SHARED
	${ProxyLogicPlugin_ROOT_Cpp}
	${ProxyLogicPlugin_ROOT_Hpp})
	
set_target_properties( proxy_logic_plugin PROPERTIES OUTPUT_NAME "logic")
set_target_properties( proxy_logic_plugin PROPERTIES PREFIX "")
set_target_properties( proxy_logic_plugin PROPERTIES 
	FOLDER "server/plugin/proxy_logic"
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/proxy
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/proxy
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/proxy )

add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)