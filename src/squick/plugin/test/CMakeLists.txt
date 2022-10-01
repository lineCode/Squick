set(ProjectName "test")
file(GLOB test_plugin_ROOT_Cpp
	*.cc)
	
file(GLOB test_plugin_ROOT_Hpp 
	*.h)

add_library(test SHARED
	${test_plugin_ROOT_Cpp}
	${test_plugin_ROOT_Hpp})
	
set_target_properties( test PROPERTIES OUTPUT_NAME "test")
set_target_properties( test PROPERTIES PREFIX "")
set_target_properties( test PROPERTIES 
	FOLDER "squick/test"
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )

#link_NFSDK("test_plugin")

if(UNIX)
	target_link_libraries(test -static-libstdc++)

	add_definitions(
		-DELPP_NO_DEFAULT_LOG_FILE
	)
	
else()

	target_link_libraries(test -static-libstdc++)
	
	add_definitions(
		-DWIN
		-DELPP_NO_DEFAULT_LOG_FILE
	)
endif()
