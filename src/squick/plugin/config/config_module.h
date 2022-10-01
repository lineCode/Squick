
#ifndef SQUICK_COMMONCONFIG_MODULE_H
#define SQUICK_COMMONCONFIG_MODULE_H

#include "squick/base/common_config.h"
#include "squick/base/plugin_manager.h"

class ConfigModule
    : public ICommonConfigModule
{
public:
public:
	class CAttributeList : public MapEx<std::string, std::string>
	{
	public:
		const int GetInt(const std::string& name)
		{
			SQUICK_SHARE_PTR<std::string> pStr = GetElement(name);
			if (pStr && !pStr->empty())
			{
				int nData = 0;
				SQUICK_StrTo(*pStr, nData);
				return nData;
			}

			return 0;
		}

		const std::string& GetString(const std::string& name)
		{
			SQUICK_SHARE_PTR<std::string> pStr = GetElement(name);
			if (pStr)
			{
				return *pStr;
			}

			return NULL_STR;
		}
	};

	struct CStructInfo : public MapEx<std::string, CAttributeList>
	{
		CAttributeList  mmStructAttribute;
	};

public:
    ConfigModule( IPluginManager* p )
    {
        pPluginManager = p;
    }
    virtual ~ConfigModule() {};

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();
    virtual bool AfterInit();

	virtual bool ClearConfig();
	virtual bool LoadConfig(const std::string& strFile);

	virtual const int GetFieldInt(const std::string& strStructName, const std::string& strStructItemName, const std::string& strAttribute);
	virtual const int GetFieldInt(const std::string& strStructName, const std::string& strSDKAttribute);
	
	virtual const std::string& GetFieldString(const std::string& strStructName, const std::string& strStructItemName, const std::string& strAttribute);
	virtual const std::string& GetFieldString(const std::string& strStructName,const std::string& strSDKAttribute);
	
	virtual std::vector<std::string> GetSubKeyList(const std::string&strStructName);
	virtual std::vector<std::string> GetFieldList(const std::string&strStructName);

private:
	MapEx<std::string, CStructInfo> mmData; //strStructName<-->CStructInfo
};


#endif
