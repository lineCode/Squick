cmake_minimum_required(VERSION 2.8)

set_property(GLOBAL PROPERTY USE_FOLDERS On)

option(BUILD_TOOLS_ONLY "help string describing option" OFF)
option(BUILD_MID_WARE_SDK "help string describing option" OFF)


macro(link_NFSDK projName)
	add_dependencies(${projName} core struct net_plugin)
	target_link_libraries(${projName} core struct net_plugin)
endmacro(link_NFSDK)
project(Squick)

set(SolutionDir ${PROJECT_SOURCE_DIR})


set(SQUICK_BUILD_EXTEND_PLUGIN_PATH ${PROJECT_SOURCE_DIR}/build/server/plugin/extend)
set(SQUICK_BUILD_EXE_PATH ${PROJECT_SOURCE_DIR}/build/server)
set(SQUICK_BUILD_CORE_PLUGIN_PATH ${PROJECT_SOURCE_DIR}/build/server/plugin/core)
set(SQUICK_RUNTIME_LIB_PATH ${PROJECT_SOURCE_DIR}/build/server/lib)

message("NFOutPutDir:${NFOutPutDir}")


message(STATUS "SolutionDir=" ${SolutionDir})

include_directories(
	${SolutionDir}
	${SolutionDir}/src/
	${SolutionDir}/third_party/
	${SolutionDir}/third_party/build/include
	${SolutionDir}/third_party/zlib
	)

message("Build Type:"${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS})


if( CMAKE_BUILD_TYPE STREQUAL "debug" )
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fPIC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17  -g -ggdb -DDEBUG -fPIC -Wendif-labels") # -O0 -Wall
else()
	set(CMAKE_BUILD_TYPE "release")
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fPIC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -O3 -fPIC -std=c++17  -Wendif-labels")# 
	
endif()

set(LDFLAGS "$ENV{LDFLAGS} -stdlib=libc++")
#add_definitions(-std=c++17)


if( CMAKE_BUILD_TYPE STREQUAL "debug" )
	set(ThirdPartyLibPath ${SolutionDir}/third_party/build/lib ${SolutionDir}/build/debug/lib )
else()
	set(ThirdPartyLibPath ${SolutionDir}/third_party/build/lib ${SolutionDir}/build/release/lib)
endif()


link_directories(${ThirdPartyLibPath})

if(${BUILD_TOOLS_ONLY} STREQUAL "ON")
	message("Build Tools Only")
	add_subdirectory(src/tools)
else()
	add_definitions(-D_X64 -D_CONSOLE -DSQUICK_DYNAMIC_PLUGIN )
	message("Build Squicks")
	add_subdirectory(src/squick)
	add_subdirectory(src/server)
	add_subdirectory(src/tutorial)
endif()
