set(ProjectName "squick_struct")


file(GLOB NFMessageDefine_ROOT_CC *.cc)
file(GLOB NFMessageDefine_ROOT_Hpp *.h)
# 采用静态编译塞入可执行文件里，由于可执行程序内没有直接调用里面的函数，不存在关系，所以就不能链接关系。

add_library(squick_struct SHARED 
	${NFMessageDefine_ROOT_CC}
	${NFMessageDefine_ROOT_Hpp})

add_definitions(
	-D_THREAD_SAFE
)
target_link_libraries(squick_struct libprotobuf.so)

set_target_properties( squick_struct PROPERTIES OUTPUT_NAME "squick_struct")
set_target_properties( squick_struct PROPERTIES PREFIX "")
set_target_properties( squick_struct PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH} )