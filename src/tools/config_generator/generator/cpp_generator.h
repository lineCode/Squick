//
// Created by i0gan 2022-09-19
//

#ifndef NFCPPGENERATOR_HPP
#define NFCPPGENERATOR_HPP

#include "../generator.h"

namespace squick::tools::file_process {
class CPPGenerator : public NFIGenerator
{
public:
	CPPGenerator(){}

	virtual bool Generate(const std::map<std::string, ClassData*>& classData) override
	{
		FILE* hppWriter = fopen("../proto/protocol_define.h", "w");

		std::string strFileHead;

		strFileHead = strFileHead
		              + "// -------------------------------------------------------------------------\n"
		              + "//    @FileName         :    protocol_define.h\n"
		              + "//    @Author           :    Pwnsky\n"
		              + "//    @Module           :    ProtocolDefine\n"
		              + "// -------------------------------------------------------------------------\n\n"
		              + "#ifndef SQUICK_PR_NAME_HPP\n"
		              + "#define SQUICK_PR_NAME_HPP\n\n"
		              + "#include <string>\n"
		              + "namespace SquickProtocol\n{\n";

		fwrite(strFileHead.c_str(), strFileHead.length(), 1, hppWriter);
		/////////////////////////////////////////////////////

		ClassData* pBaseObject = classData.at("IObject");
		std::string instanceField = "\n";

		for (std::map<std::string, ClassData*>::const_iterator it = classData.begin(); it != classData.end(); ++it)
		{
			const std::string& className = it->first;
			ClassData* pClassDta = it->second;

			if (pClassDta->beIncluded || pClassDta->beParted || className == "Include")
			{
				continue;
			}

			// cpp
			std::string strPropertyInfo;

			strPropertyInfo += "\tclass " + className + "\n\t{\n\tpublic:\n";
			strPropertyInfo += "\t\t//Class name\n\t";
			strPropertyInfo += "\tstatic const std::string& ThisName(){ static std::string x = \"" + className + "\"; return x; };";

			instanceField += "\tconst std::string " + className + "::ThisName = \"" + className + "\";\n";

			if (className != "IObject")
			{
				//add base class properties
				strPropertyInfo += "\t\t// IObject\n";

				for (std::map<std::string, ClassProperty*>::iterator itProperty = pBaseObject->xStructData.xPropertyList.begin();
				     itProperty != pBaseObject->xStructData.xPropertyList.end(); ++itProperty)
				{
					const std::string& propertyName = itProperty->first;
					ClassProperty* pClassProperty = itProperty->second;

					strPropertyInfo += "\t\tstatic const std::string& " + propertyName + "(){ static std::string x = \"" + propertyName + "\"; return x; };";
					strPropertyInfo += "// " + pClassProperty->descList["Type"] + "\n";

					instanceField += "\tconst std::string " + className + "::" + propertyName + " = \"" + propertyName + "\";\n";
				}
			}

			strPropertyInfo += "\t\t// Property\n";
			for (std::map<std::string, ClassProperty*>::iterator itProperty = pClassDta->xStructData.xPropertyList.begin();
			     itProperty != pClassDta->xStructData.xPropertyList.end(); ++itProperty)
			{
				const std::string& propertyName = itProperty->first;
				ClassProperty* pClassProperty = itProperty->second;

				strPropertyInfo += "\t\tstatic const std::string& " + propertyName + "(){ static std::string x = \"" + propertyName + "\"; return x; };";
				strPropertyInfo += "// " + pClassProperty->descList["Type"] + "\n";

				instanceField += "\tconst std::string " + className + "::" + propertyName + " = \"" + propertyName + "\";\n";
			}


			//include property, come from


			for (std::string item : pClassDta->includes)
			{
				auto includeClass = classData.at(item);

				strPropertyInfo += "\t\t// Include Property, come from " + includeClass->xStructData.className + " \n";

				for (std::map<std::string, ClassProperty*>::iterator itProperty = includeClass->xStructData.xPropertyList.begin();
				     itProperty != includeClass->xStructData.xPropertyList.end(); ++itProperty)
				{
					const std::string& propertyName = itProperty->first;
					ClassProperty* pClassProperty = itProperty->second;

					strPropertyInfo += "\t\tstatic const std::string& " + propertyName + "(){ static std::string x = \"" + propertyName + "\"; return x; };";
					strPropertyInfo += "// " + pClassProperty->descList["Type"] + "\n";

					instanceField += "\tconst std::string " + className + "::" + propertyName + " = \"" + propertyName + "\";\n";
				}
			}

			fwrite(strPropertyInfo.c_str(), strPropertyInfo.length(), 1, hppWriter);

			//record
			std::string strRecordInfo = "";
			strRecordInfo += "\t\t// Record\n";

			for (std::map<std::string, NFClassRecord*>::iterator itRecord = pClassDta->xStructData.xRecordList.begin();
			     itRecord != pClassDta->xStructData.xRecordList.end(); ++itRecord)
			{
				const std::string& recordName = itRecord->first;
				NFClassRecord* pClassRecord = itRecord->second;

				std::cout << "save for cpp ---> " << className  << "::" << recordName << std::endl;

				strRecordInfo += "\t\tclass " + recordName + "\n\t\t{\n\t\tpublic:\n";
				strRecordInfo += "\t\t\t//Class name\n\t";
				strRecordInfo += "\t\tstatic const std::string& ThisName(){ static std::string x = \"" + recordName + "\"; return x; };\n";

				instanceField += "\tconst std::string " + className + "::" + recordName + "::ThisName = \"" + recordName + "\";\n";

				//col
				for (int i = 0; i < pClassRecord->colList.size(); ++i)
				{
					for (std::map<std::string, NFClassRecord::RecordColDesc*>::iterator itCol = pClassRecord->colList.begin();
					     itCol != pClassRecord->colList.end(); ++itCol)
					{
						const std::string& colTag = itCol->first;
						NFClassRecord::RecordColDesc* pRecordColDesc = itCol->second;

						if (pRecordColDesc->index == i)
						{
							strRecordInfo += "\t\t\tstatic const int " + colTag + " = " + std::to_string(pRecordColDesc->index) + ";//" + pRecordColDesc->type + "\n";
						}
					}
				}

				strRecordInfo += "\n\t\t};\n";

			}

			//include record

			for (std::string item : pClassDta->includes)
			{
				auto includeClass = classData.at(item);

				strPropertyInfo += "\t\t// Include Record, come from " + includeClass->xStructData.className + " \n";

				for (std::map<std::string, NFClassRecord*>::iterator itRecord = includeClass->xStructData.xRecordList.begin();
				     itRecord != includeClass->xStructData.xRecordList.end(); ++itRecord)
				{
					const std::string& recordName = itRecord->first;
					NFClassRecord* pClassRecord = itRecord->second;

					strRecordInfo += "\t\tclass " + recordName + "\n\t\t{\n\t\tpublic:\n";
					strRecordInfo += "\t\t\t//Class name\n\t";
					strRecordInfo += "\t\tstatic const std::string& ThisName(){ static std::string x = \"" + recordName + "\"; return x; };\n";

					instanceField += "\tconst std::string " + className + "::" + recordName + "::ThisName = \"" + recordName + "\";\n";

					//col
					for (int i = 0; i < pClassRecord->colList.size(); ++i)
					{
						for (std::map<std::string, NFClassRecord::RecordColDesc*>::iterator itCol = pClassRecord->colList.begin();
						     itCol != pClassRecord->colList.end(); ++itCol)
						{
							const std::string& colTag = itCol->first;
							NFClassRecord::RecordColDesc* pRecordColDesc = itCol->second;

							if (pRecordColDesc->index == i)
							{
								strRecordInfo += "\t\t\tstatic const int " + colTag + " = " + std::to_string(pRecordColDesc->index) + ";//" + pRecordColDesc->type + "\n";
							}
						}
					}

					strRecordInfo += "\n\t\t};\n";

				}
			}

			fwrite(strRecordInfo.c_str(), strRecordInfo.length(), 1, hppWriter);

			std::string strHppEnumInfo = "";


			std::string strClassEnd;
			strClassEnd += "\n\t};\n";

			fwrite(strClassEnd.c_str(), strClassEnd.length(), 1, hppWriter);

		}

		//fwrite(instanceField.c_str(), instanceField.length(), 1, hppWriter);

		std::string strFileEnd = "\n}\n#endif";
		fwrite(strFileEnd.c_str(), strFileEnd.length(), 1, hppWriter);
		/////////////////////////////////////////////////////

		/////////////////////////////////////////////////////

		fclose(hppWriter);

		return false;
	}
};
}
#endif //NFCPPGENERATOR_HPP
