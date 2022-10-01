file(GLOB CORE_ROOT_CC
	*.cc)
file(GLOB CORE_ROOT_H
	*.h)

add_library(squick_core SHARED ${CORE_ROOT_H} ${CORE_ROOT_CC})

target_link_libraries(squick_core  squick_struct)
add_dependencies(squick_core  squick_struct)

add_definitions(-DSQUICK_NONCLIENT_BUILD)
set_target_properties( squick_core PROPERTIES OUTPUT_NAME "skcore")
set_target_properties( squick_core PROPERTIES PREFIX "")
set_target_properties( squick_core PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH} )
	
if(UNIX)
	if (CMAKE_BUILD_TYPE MATCHES "release")
		target_link_libraries(squick_core )
	else()
		#target_link_libraries(squick_core )
	endif()

	target_link_libraries(squick_core -static-libstdc++)
else()
	#target_link_libraries(squick_core )
	#target_link_libraries(squick_core -static-libstdc++)
endif()

