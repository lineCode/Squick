file(GLOB tnavigation_ROOT_Cpp *.cpp)
file(GLOB tnavigation_ROOT_Hpp *.hpp)
file(GLOB tnavigation_ROOT_H *.h)

set(ThirdPartyLibPath ../build/lib)

add_compile_options(-fPIC)
add_library(tnavigation 
	${tnavigation_ROOT_Cpp} 
	${tnavigation_ROOT_H} 
	${tnavigation_ROOT_Hpp})

add_definitions(-DNF_NONCLIENT_BUILD)
set_target_properties( tnavigation PROPERTIES OUTPUT_NAME "tnavigation")

if( WIN32 )
    set_target_properties( tnavigation PROPERTIES PREFIX "")
endif()

set_target_properties( tnavigation PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY .
	RUNTIME_OUTPUT_DIRECTORY .
	LIBRARY_OUTPUT_DIRECTORY . )
	

target_link_libraries(tnavigation)
target_link_libraries(tnavigation -static-libstdc++)
