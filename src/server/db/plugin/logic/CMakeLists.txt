set(ProjectName "db_logic_plugin")
file(GLOB NFDataAgent_NosqlPlugin_ROOT_Cpp
	*.cc)

file(GLOB NFDataAgent_NosqlPlugin_ROOT_Hpp 
	*.h)

add_library(db_logic_plugin SHARED
	${NFDataAgent_NosqlPlugin_ROOT_Cpp}
	${NFDataAgent_NosqlPlugin_ROOT_Hpp})
	
set_target_properties( db_logic_plugin PROPERTIES OUTPUT_NAME "logic")
set_target_properties( db_logic_plugin PROPERTIES PREFIX "")
set_target_properties( db_logic_plugin PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db )
	
add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
	