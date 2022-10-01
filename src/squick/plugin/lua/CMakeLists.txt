set(ProjectName "lua")
file(GLOB LuaScriptPlugin_ROOT_Cpp *.cc)
file(GLOB LuaScriptPlugin_ROOT_Hpp *.h)

add_library(lua SHARED
	${LuaScriptPlugin_ROOT_Cpp}
	${LuaScriptPlugin_ROOT_Hpp})

target_link_libraries(lua liblua.a libprotobuf.so)
add_dependencies(lua squick_struct)

set_target_properties( lua PROPERTIES OUTPUT_NAME "lua")
set_target_properties( lua PROPERTIES PREFIX "")
set_target_properties( lua PROPERTIES
	FOLDER "squick/lua"
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )