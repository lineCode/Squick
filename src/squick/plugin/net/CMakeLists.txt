set(ProjectName "net")

file(GLOB Net_ROOT_Cpp *.cc)
file(GLOB Net_ROOT_Hpp *.h)

#Exclude this file
#file(GLOB RemoveItems_Cpp TestClient.cpp TestServer.cpp)
#list(REMOVE_ITEM Net_ROOT_Cpp ${RemoveItems_Cpp})

add_library(net SHARED ${Net_ROOT_Cpp} ${Net_ROOT_Hpp})

add_definitions(-DSQUICK_NONCLIENT_BUILD)
set_target_properties( net PROPERTIES OUTPUT_NAME "net")
set_target_properties( net PROPERTIES PREFIX "")
set_target_properties( net PROPERTIES
	FOLDER "squick/net_plugin"
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH})

	#add_dependencies(net)
	
if(UNIX)
		target_link_libraries(net libevent.a)
		target_link_libraries(net libevent_core.a)
		target_link_libraries(net libevent_extra.a)
		#target_link_libraries(net_plugin libevent_openssl.a)
		#target_link_libraries(net_plugin libssl.a)
		#target_link_libraries(net_plugin libcrypto.a)
		target_link_libraries(net squick_struct)
		target_link_libraries(net -static-libstdc++)
	add_definitions(
		-D_THREAD_SAFE
	)
else()



endif()