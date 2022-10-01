set(ProjectName "actor")
file(GLOB ActorPlugin_ROOT_CC *.cc)
file(GLOB ActorPlugin_ROOT_H *.h)

add_library(actor SHARED
	${ActorPlugin_ROOT_CC}
	${ActorPlugin_ROOT_H})
	
set_target_properties( actor PROPERTIES OUTPUT_NAME "actor")
set_target_properties( actor PROPERTIES PREFIX "")
set_target_properties( actor PROPERTIES
	FOLDER "squick/actor"
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )