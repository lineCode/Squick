set(ProjectName "chat_plugin")
file(GLOB NFTutorialChatPlugin_ROOT_Cpp
	*.cc)
	
file(GLOB NFTutorialChatPlugin_ROOT_Hpp 
	*.h)

add_library(chat_plugin SHARED
	${NFTutorialChatPlugin_ROOT_Cpp}
	${NFTutorialChatPlugin_ROOT_Hpp})
	
set_target_properties( chat_plugin PROPERTIES OUTPUT_NAME "chat")
set_target_properties( chat_plugin PROPERTIES PREFIX "")
set_target_properties( chat_plugin PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/others
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/others
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/others )

add_definitions(-D_X64 -D_CONSOLE)
