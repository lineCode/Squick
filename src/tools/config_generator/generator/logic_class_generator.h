//
// Created by James on 7/02/21.
//

#ifndef NFLOGICCLASSGENERATOR_HPP
#define NFLOGICCLASSGENERATOR_HPP
#include "../generator.h"
namespace squick::tools::file_process {
class LogicClassGenerator : public NFIGenerator
{
public:
	LogicClassGenerator()
	{
	}

	virtual bool Generate(const std::map<std::string, ClassData *> &classData) override
	{

		std::string fileName = strXMLStructPath + "logic_class.xml";

		FILE* iniWriter = fopen(fileName.c_str(), "w");

		std::string strFileHead = "<?xml version='1.0' encoding='utf-8' ?>\n<XML>\n";
		fwrite(strFileHead.c_str(), strFileHead.length(), 1, iniWriter);

		ClassData* pBaseObject = classData.at("IObject");

		std::string strElementData;
		strElementData += "\t<Class Id=\"" + pBaseObject->xStructData.className + "\"\t";

		std::string path = pBaseObject->filePath;
		ConfigGeneratorHelp::StringReplace(path, strExcelIniPath, "");

		strElementData += "Path=\"config/struct/" + path + ".xml\"\t";
		strElementData += "InstancePath=\"config/ini/" + path + ".xml\"\t>\n"; // 已修复bug

		for (std::map<std::string, ClassData*>::const_iterator it = classData.begin(); it != classData.end(); ++it)
		{
			const std::string& className = it->first;
			ClassData* pClassDta = it->second;
			if (className == "IObject")
			{
				continue;
			}

			if (it->second->beIncluded || it->second->beParted)
			{
				continue;
			}

			strElementData += "\t\t<Class Id=\"" + pClassDta->xStructData.className + "\"\t";

			std::string path = pClassDta->filePath;
			ConfigGeneratorHelp::StringReplace(path, strExcelIniPath, "");

			strElementData += "Path=\"config/struct/" + path + ".xml\"\t";
			strElementData += "InstancePath=\"config/ini/" + path + ".xml\"\t/>\n";

		}

		strElementData += "\t</Class>\n";
		fwrite(strElementData.c_str(), strElementData.length(), 1, iniWriter);

		std::string strFileEnd = "</XML>";
		fwrite(strFileEnd.c_str(), strFileEnd.length(), 1, iniWriter);

		return false;
	}
};
}
#endif //NFLOGICCLASSGENERATOR_HPP
