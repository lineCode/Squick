set(ProjectName "squick")

file(GLOB Squick_ROOT_Cpp *.cc)
file(GLOB Squick_ROOT_Hpp *.h)


add_executable(squick ${Squick_ROOT_Cpp} ${Squick_ROOT_Hpp})

#link_NFSDK("Squick")


add_dependencies(squick  squick_struct)
target_link_libraries(squick squick_core squick_plugin_loader)
add_dependencies(squick squick_core squick_plugin_loader)
target_link_libraries( squick -static-libstdc++ -pthread libprotobuf.so)

#SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#SET(BUILD_SHARED_LIBRARIES OFF)
#SET(CMAKE_EXE_LINKER_FLAGS "-static")

set_target_properties( squick PROPERTIES OUTPUT_NAME "squick")
set_target_properties( squick PROPERTIES
	FOLDER "squick/squick"
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXE_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXE_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXE_PATH} )

add_definitions(-D_X64 -D_CONSOLE)


add_subdirectory(db)
add_subdirectory(login)
add_subdirectory(game)
add_subdirectory(master)
add_subdirectory(proxy)
add_subdirectory(world)

add_subdirectory(others)

