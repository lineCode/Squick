set(ProjectName "logic")
file(GLOB GameServerPlugin_ROOT_Cpp
	*.cc)

file(GLOB GameServerPlugin_ROOT_Hpp 
	*.h)	

add_library(logic SHARED
	${GameServerPlugin_ROOT_Cpp}
	${GameServerPlugin_ROOT_Hpp})

set_target_properties( logic PROPERTIES OUTPUT_NAME "logic")
set_target_properties( logic PROPERTIES PREFIX "")
set_target_properties( logic PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/game
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/game
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/game )

add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
