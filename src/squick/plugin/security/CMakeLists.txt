set(ProjectName "security")
file(GLOB security_plugin_root_cc
	*.cc)
	
file(GLOB security_plugin_root_h 
	*.h)

add_library(security SHARED
	${security_plugin_root_cc}
	${security_plugin_root_h})
	
set_target_properties( security PROPERTIES OUTPUT_NAME "security")
set_target_properties( security PROPERTIES PREFIX "")
set_target_properties( security PROPERTIES 
	FOLDER "squick/security"
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )


target_link_libraries(security -static-libstdc++)
add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)

