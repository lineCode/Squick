#pragma once


#include "config_generator_data.h"
#include "config_generator_help.h"
namespace squick::tools::file_process {
class NFIGenerator
{
public:
	virtual bool Generate(const std::map<std::string, ClassData*>& classData) = 0;

	std::string strExcelIniPath = "../excel/";
	std::string strXMLStructPath = "../struct/";
	std::string strXMLIniPath = "../ini/";

};

}
