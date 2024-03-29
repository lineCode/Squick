//
// Created by James on 7/02/21.
//

#ifndef NFJAVAGENERATOR_H
#define NFJAVAGENERATOR_H
#include "../generator.h"
namespace squick::tools::file_process {
class JAVAGenerator : public NFIGenerator
{
public:
	JAVAGenerator()
	{
	}

	virtual bool Generate(const std::map<std::string, ClassData *> &classData) override
	{

		FILE* javaWriter = fopen("../proto/ProtocolDefine.java", "w");

		std::string strFileHead
				= "// -------------------------------------------------------------------------\n";
		strFileHead = strFileHead
		              + "//    @FileName         :    ProtocolDefine.java\n"
		              + "//    @Author           :    Pwnsky\n"
		              + "//    @Module           :    ProtocolDefine\n"
		              + "// -------------------------------------------------------------------------\n\n"
		              + "package nframe;\n";

		fwrite(strFileHead.c_str(), strFileHead.length(), 1, javaWriter);
		/////////////////////////////////////////////////////

		ClassData* pBaseObject = classData.at("IObject");
		for (std::map<std::string, ClassData*>::const_iterator it = classData.begin(); it != classData.end(); ++it)
		{
			const std::string& className = it->first;
			ClassData* pClassDta = it->second;

			if (pClassDta->beIncluded || pClassDta->beParted || className == "Include")
			{
				continue;
			}

			// cs
			std::string strPropertyInfo;

			strPropertyInfo += "\tpublic class " + className + "\n\t{\n";
			strPropertyInfo += "\t\t//Class name\n\t";
			strPropertyInfo += "\tpublic static final String ThisName = \"" + className + "\";\n";

			if (className != "IObject")
			{
				//add base class properties
				strPropertyInfo += "\t\t// IObject\n";

				for (std::map<std::string, ClassProperty*>::iterator itProperty = pBaseObject->xStructData.xPropertyList.begin();
				     itProperty != pBaseObject->xStructData.xPropertyList.end(); ++itProperty)
				{
					const std::string& propertyName = itProperty->first;
					ClassProperty* pClassProperty = itProperty->second;

					strPropertyInfo += "\t\tpublic static final String " + propertyName + " = \"" + propertyName + "\";";
					strPropertyInfo += "// " + pClassProperty->descList["Type"] + "\n";
				}
			}

			strPropertyInfo += "\t\t// Property\n";
			for (std::map<std::string, ClassProperty*>::iterator itProperty = pClassDta->xStructData.xPropertyList.begin();
			     itProperty != pClassDta->xStructData.xPropertyList.end(); ++itProperty)
			{
				const std::string& propertyName = itProperty->first;
				ClassProperty* pClassProperty = itProperty->second;

				strPropertyInfo += "\t\tpublic static final String " + propertyName + " = \"" + propertyName + "\";";
				strPropertyInfo += "// " + pClassProperty->descList["Type"] + "\n";
			}

			fwrite(strPropertyInfo.c_str(), strPropertyInfo.length(), 1, javaWriter);

			//record
			std::string strRecordInfo = "";
			strRecordInfo += "\t\t// Record\n";

			for (std::map<std::string, NFClassRecord*>::iterator itRecord = pClassDta->xStructData.xRecordList.begin();
			     itRecord != pClassDta->xStructData.xRecordList.end(); ++itRecord)
			{
				const std::string& recordName = itRecord->first;
				NFClassRecord* pClassRecord = itRecord->second;

				std::cout << "save for java ---> " << className << "::" << recordName << std::endl;

				strRecordInfo += "\t\tpublic class " + recordName + "\n\t\t{\n";
				strRecordInfo += "\t\t\t//Class name\n\t";
				strRecordInfo += "\t\tpublic static final String ThisName = \"" + recordName + "\";\n";

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
							strRecordInfo += "\t\t\tpublic static final int " + colTag + " = " + std::to_string(pRecordColDesc->index) + ";//" + pRecordColDesc->type + "\n";
						}
					}
				}

				strRecordInfo += "\n\t\t}\n";

			}
			fwrite(strRecordInfo.c_str(), strRecordInfo.length(), 1, javaWriter);

			std::string strHppEnumInfo = "";


			std::string strClassEnd;
			strClassEnd += "\n\t}\n";

			fwrite(strClassEnd.c_str(), strClassEnd.length(), 1, javaWriter);

		}

		fclose(javaWriter);

		return false;
	}
};
}
#endif //NFJAVAGENERATOR_H
