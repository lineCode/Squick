set(ProjectName "kernel")

file(GLOB KernelPlugin_ROOT_Cpp *.cc)
file(GLOB KernelPlugin_ROOT_Hpp *.h)

add_library(kernel SHARED
	${KernelPlugin_ROOT_Cpp}
	${KernelPlugin_ROOT_Hpp})

#add_dependencies(kernel_plugin core config_plugin)		
#target_link_libraries(kernel_plugin  core)
#target_link_libraries(kernel_plugin -static-libstdc++)


set_target_properties( kernel PROPERTIES OUTPUT_NAME "kernel")
set_target_properties( kernel PROPERTIES PREFIX "")
set_target_properties( kernel PROPERTIES
	FOLDER "squick/kernel"
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )

