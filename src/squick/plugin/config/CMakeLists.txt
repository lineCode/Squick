set(ProjectName "config")
file(GLOB ConfigPlugin_ROOT_CC
	*.cc)

file(GLOB ConfigPlugin_ROOT_H
	*.h)
add_library(config SHARED ${ConfigPlugin_ROOT_CC} ${ConfigPlugin_ROOT_H})

set_target_properties( config PROPERTIES OUTPUT_NAME "config")
set_target_properties( config PROPERTIES PREFIX "")
set_target_properties( config PROPERTIES 
	FOLDER "squick/config"
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )


#add_dependencies(config core)
# target_link_libraries(config_plugin  core)
# target_link_libraries(config_plugin -static-libstdc++)

