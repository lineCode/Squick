set(ProjectName "navigation")
file(GLOB Navigation_ROOT_CC *.cc)
file(GLOB Navigation_ROOT_H *.h)
	
add_library(navigation SHARED
	${Navigation_ROOT_CC}
	${Navigation_ROOT_H})

target_include_directories(navigation PUBLIC
	${SolutionDir}/third_party/navigation/)

if (CMAKE_BUILD_TYPE MATCHES "release")
	target_link_libraries(navigation tnavigation)
else()
	target_link_libraries(navigation tnavigation)
endif()

	target_link_libraries(navigation -static-libstdc++)

#link_NFSDK("navigation_plugin")
set_target_properties( navigation PROPERTIES OUTPUT_NAME "navigation")
set_target_properties( navigation PROPERTIES PREFIX "")
set_target_properties( navigation PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )