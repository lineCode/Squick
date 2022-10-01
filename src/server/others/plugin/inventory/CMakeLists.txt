set(ProjectName "inventory_plugin")
file(GLOB NFTutorialInventoryPlugin_ROOT_Cpp
	*.cc)
	
file(GLOB NFTutorialInventoryPlugin_ROOT_Hpp
	*.h)

add_library(inventory_plugin SHARED
	${NFTutorialInventoryPlugin_ROOT_Cpp}
	${NFTutorialInventoryPlugin_ROOT_Hpp})
	
set_target_properties( inventory_plugin PROPERTIES OUTPUT_NAME "inventory")
set_target_properties( inventory_plugin PROPERTIES PREFIX "")
set_target_properties( inventory_plugin PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/others
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/others
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/others )

add_definitions(-D_X64 -D_CONSOLE)