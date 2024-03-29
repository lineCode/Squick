include_directories(
	minizip
	tinyxml2
	zlib
	mini_excel_reader)

file(GLOB ConfigGenerator_MiniExcelReader_Cpp ./mini_excel_reader/*.cc)
file(GLOB ConfigGenerator_MiniExcelReader_Hpp ./mini_excel_reader/*.h)
file(GLOB ConfigGenerator_minizip_C ${SolutionDir}/third_party/minizip/ioapi.c ${SolutionDir}/third_party/minizip/ioapi_mem.c ${SolutionDir}/third_party/minizip/unzip.c)
file(GLOB ConfigGenerator_minizip_Hpp ${SolutionDir}/third_party//minizip/*.h)
file(GLOB ConfigGenerator_zlib_C ${SolutionDir}/third_party/zlib/*.c)
file(GLOB ConfigGenerator_zlib_Hpp ${SolutionDir}/third_party/zlib/*.h)
file(GLOB ConfigGenerator_ROOT_Cpp *.cc)
file(GLOB ConfigGenerator_ROOT_Hpp *.h)
file(GLOB ConfigGenerator_zlib_Hpp ./generator/*.h)

source_group("mini_excel_reader" FILES ${ConfigGenerator_MiniExcelReader_Cpp})
source_group("mini_excel_reader" FILES ${ConfigGenerator_MiniExcelReader_Hpp})

source_group("minizip" FILES ${ConfigGenerator_minizip_C})
source_group("minizip" FILES ${ConfigGenerator_minizip_Hpp})

source_group("tinyxml2" FILES ${ConfigGenerator_tinyxml2_Cpp})
source_group("tinyxml2" FILES ${ConfigGenerator_tinyxml2_Hpp})

source_group("zlib" FILES ${ConfigGenerator_zlib_C})
source_group("zlib" FILES ${ConfigGenerator_zlib_Hpp})

add_executable(config_generator
	${ConfigGenerator_MiniExcelReader_Cpp} 
	${ConfigGenerator_MiniExcelReader_Hpp} 
	${ConfigGenerator_minizip_C} 
	${ConfigGenerator_minizip_Hpp}
	${ConfigGenerator_tinyxml2_Cpp} 
	${ConfigGenerator_tinyxml2_Hpp}
	${ConfigGenerator_zlib_C} 
	${ConfigGenerator_zlib_Hpp}
	${ConfigGenerator_ROOT_Cpp}
	${ConfigGenerator_ROOT_Hpp})

set_target_properties( config_generator PROPERTIES OUTPUT_NAME "config_generator")
set_target_properties( config_generator PROPERTIES
	FOLDER "tools"
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${SolutionDir}/build/config/tools/
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${SolutionDir}/build/config/tools/
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${SolutionDir}/build/config/tools/
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${SolutionDir}/build/config/tools/
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${SolutionDir}/build/config/tools/
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${SolutionDir}/build/config/tools/)

add_definitions(
	-D_CRT_SECURE_NO_WARNINGS
	-D_CRT_NONSTDC_NO_DEPRECATE
)
