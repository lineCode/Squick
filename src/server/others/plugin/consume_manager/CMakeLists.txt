set(ProjectName "consume_manager_plugin")
file(GLOB ConsumeManagerPlugin_ROOT_Cpp
	*.cc)
	
file(GLOB ConsumeManager_ROOT_Hpp
	*.h)

add_library(consume_manager_plugin SHARED
	${ConsumeManagerPlugin_ROOT_Cpp}
	${ConsumeManager_ROOT_Hpp})
	
set_target_properties( consume_manager_plugin PROPERTIES OUTPUT_NAME "consume_manager")
set_target_properties( consume_manager_plugin PROPERTIES PREFIX "")
set_target_properties( consume_manager_plugin PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/others
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/others
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/others )

add_definitions(-D_X64 -D_CONSOLE)