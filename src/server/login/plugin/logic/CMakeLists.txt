set(ProjectName "login_logic_plugin")
file(GLOB LoginLogicPlugin_ROOT_Cpp
	*.cc)

file(GLOB LoginLogicPlugin_ROOT_Hpp 
	*.h)

add_library(login_logic_plugin SHARED
	${LoginLogicPlugin_ROOT_Cpp}
	${LoginLogicPlugin_ROOT_Hpp})
	
set_target_properties( login_logic_plugin PROPERTIES OUTPUT_NAME "logic")
set_target_properties( login_logic_plugin PROPERTIES PREFIX "")
set_target_properties( login_logic_plugin PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/login
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/login
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/login )


add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
