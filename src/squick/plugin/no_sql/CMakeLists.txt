set(ProjectName "nosql")

set(ProjectName "nosql")
file(GLOB NoSqlPlugin_ROOT_Cpp
		*.cc)

file(GLOB NoSqlPlugin_ROOT_Hpp
		*.h)

add_library(nosql SHARED
		${NoSqlPlugin_ROOT_Cpp}
		${NoSqlPlugin_Hpp})

set_target_properties( nosql PROPERTIES OUTPUT_NAME "nosql")
set_target_properties( nosql PROPERTIES PREFIX "")
set_target_properties( nosql PROPERTIES
		FOLDER "squick/nosql"
		ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
		RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
		LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )

#link_NFSDK("no_sql_plugin")


if (CMAKE_BUILD_TYPE MATCHES "release")
	target_link_libraries(nosql hiredis.a)
else()
	target_link_libraries(nosql hiredis.a)
endif()

target_link_libraries(nosql -static-libstdc++)

add_definitions(
		-DELPP_NO_DEFAULT_LOG_FILE
)


