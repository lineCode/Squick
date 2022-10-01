set(ProjectName "log")
file(GLOB LogPlugin_ROOT_Cpp *.cc)
file(GLOB LogPlugin_ROOT_Hpp *.h)

add_library(log SHARED
	${LogPlugin_ROOT_Cpp}
	${LogPlugin_ROOT_Hpp})

if(UNIX)

	if (CMAKE_BUILD_TYPE MATCHES "release")
	else()
	endif()
	#add_dependencies(log core )
	#target_link_libraries(log -static-libstdc++)
else()
	#add_dependencies(log core )
	#target_link_libraries(log -static-libstdc++)
endif()

set_target_properties( log PROPERTIES OUTPUT_NAME "log")
set_target_properties( log PROPERTIES PREFIX "")
set_target_properties( log PROPERTIES
	FOLDER "squick/log"
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )