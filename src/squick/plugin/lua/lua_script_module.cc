

#include <assert.h>
#include "lua_pb_module.h"
#include "lua_script_module.h"
#include "lua_script_plugin.h"
#include "squick/base/kernel.h"
#define TRY_RUN_GLOBAL_SCRIPT_FUN0(strFuncName)   try {LuaIntf::LuaRef func(mLuaContext, strFuncName);  func.call<LuaIntf::LuaRef>(); }   catch (LuaIntf::LuaException& e) { cout << e.what() << endl; }
#define TRY_RUN_GLOBAL_SCRIPT_FUN1(strFuncName, arg1)  try {LuaIntf::LuaRef func(mLuaContext, strFuncName);  func.call<LuaIntf::LuaRef>(arg1); }catch (LuaIntf::LuaException& e) { cout << e.what() << endl; }
#define TRY_RUN_GLOBAL_SCRIPT_FUN2(strFuncName, arg1, arg2)  try {LuaIntf::LuaRef func(mLuaContext, strFuncName);  func.call<LuaIntf::LuaRef>(arg1, arg2); }catch (LuaIntf::LuaException& e) { cout << e.what() << endl; }

#define TRY_LOAD_SCRIPT_FLE(fileName)  try{mLuaContext.doFile(fileName);} catch (LuaIntf::LuaException& e) { cout << e.what() << endl; }

bool LuaScriptModule::Awake()
{
	mnTime = pPluginManager->GetNowTime();

	m_pKernelModule = pPluginManager->FindModule<IKernelModule>();
	m_pClassModule = pPluginManager->FindModule<IClassModule>();
	m_pElementModule = pPluginManager->FindModule<IElementModule>();
	m_pEventModule = pPluginManager->FindModule<IEventModule>();
    m_pScheduleModule = pPluginManager->FindModule<NFIScheduleModule>();
    m_pNetClientModule = pPluginManager->FindModule<INetClientModule>();
    m_pNetModule = pPluginManager->FindModule<INetModule>();
    m_pLogModule = pPluginManager->FindModule<ILogModule>();
    m_pLuaPBModule = pPluginManager->FindModule<ILuaPBModule>();

	LuaPBModule* p = (LuaPBModule*)(m_pLuaPBModule);
	p->SetLuaState(mLuaContext.state());

    Register();
	
	// Lua执行入口
	std::string strRootFile = pPluginManager->GetConfigPath() + "script/system.lua";

	TRY_LOAD_SCRIPT_FLE(strRootFile.c_str());

	TRY_RUN_GLOBAL_SCRIPT_FUN1("init_script_system", this);

	TRY_RUN_GLOBAL_SCRIPT_FUN0("module_awake");

	return true;
}

bool LuaScriptModule::Init()
{
    TRY_RUN_GLOBAL_SCRIPT_FUN0("module_init");

    return true;
}

bool LuaScriptModule::AfterInit()
{
	TRY_RUN_GLOBAL_SCRIPT_FUN0("module_after_init");

    return true;
}

bool LuaScriptModule::Shut()
{
	TRY_RUN_GLOBAL_SCRIPT_FUN0("module_shut");

    return true;
}

bool LuaScriptModule::ReadyExecute()
{
	TRY_RUN_GLOBAL_SCRIPT_FUN0("module_ready_execute");

	return true;
}

bool LuaScriptModule::Execute()
{
    if (pPluginManager->GetNowTime() - mnTime > 10)
    {
        mnTime = pPluginManager->GetNowTime();

        OnScriptReload();
    }

    return true;
}

bool LuaScriptModule::BeforeShut()
{
    TRY_RUN_GLOBAL_SCRIPT_FUN0("module_before_shut");

    return true;
}

void LuaScriptModule::RegisterModule(const std::string & tableName, const LuaIntf::LuaRef & luaTable)
{
	mxTableName[tableName] = luaTable;
}

Guid LuaScriptModule::CreateObject(const Guid & self, const int sceneID, const int groupID, const std::string & className, const std::string & objectIndex, const DataList & arg)
{
	SQUICK_SHARE_PTR<IObject> xObject = m_pKernelModule->CreateObject(self, sceneID, groupID, className, objectIndex, arg);
	if (xObject)
	{
		return xObject->Self();

	}

	return Guid();
}

bool LuaScriptModule::ExistObject(const Guid & self)
{
	return m_pKernelModule->ExistObject(self);
}

bool LuaScriptModule::DestroyObject(const Guid & self)
{
	return m_pKernelModule->DestroyObject(self);
}

bool LuaScriptModule::EnterScene(const int sceneID, const int groupID)
{
	return false;
}

bool LuaScriptModule::DoEvent(const Guid & self, const int eventID, const DataList & arg)
{
	m_pEventModule->DoEvent(self, (int)eventID, arg);

	return true;
}

bool LuaScriptModule::FindProperty(const Guid & self, const std::string & propertyName)
{
	return m_pKernelModule->FindProperty(self, propertyName);
}

bool LuaScriptModule::SetPropertyInt(const Guid & self, const std::string & propertyName, const INT64 propValue)
{
	return m_pKernelModule->SetPropertyInt(self, propertyName, propValue);
}

bool LuaScriptModule::SetPropertyFloat(const Guid & self, const std::string & propertyName, const double propValue)
{
	return m_pKernelModule->SetPropertyFloat(self, propertyName, propValue);
}

bool LuaScriptModule::SetPropertyString(const Guid & self, const std::string & propertyName, const std::string & propValue)
{
	return m_pKernelModule->SetPropertyString(self, propertyName, propValue);
}

bool LuaScriptModule::SetPropertyObject(const Guid & self, const std::string & propertyName, const Guid & propValue)
{
	return m_pKernelModule->SetPropertyObject(self, propertyName, propValue);
}

bool LuaScriptModule::SetPropertyVector2(const Guid & self, const std::string & propertyName, const Vector2 & propValue)
{
	return m_pKernelModule->SetPropertyVector2(self, propertyName, propValue);
}

bool LuaScriptModule::SetPropertyVector3(const Guid & self, const std::string & propertyName, const Vector3 & propValue)
{
	return m_pKernelModule->SetPropertyVector3(self, propertyName, propValue);
}

INT64 LuaScriptModule::GetPropertyInt(const Guid & self, const std::string & propertyName)
{
	return m_pKernelModule->GetPropertyInt(self, propertyName);
}

int LuaScriptModule::GetPropertyInt32(const Guid & self, const std::string & propertyName)
{
	return m_pKernelModule->GetPropertyInt32(self, propertyName);
}

double LuaScriptModule::GetPropertyFloat(const Guid & self, const std::string & propertyName)
{
	return m_pKernelModule->GetPropertyFloat(self, propertyName);
}

std::string LuaScriptModule::GetPropertyString(const Guid & self, const std::string & propertyName)
{
	return m_pKernelModule->GetPropertyString(self, propertyName);
}

Guid LuaScriptModule::GetPropertyObject(const Guid & self, const std::string & propertyName)
{
	return m_pKernelModule->GetPropertyObject(self, propertyName);
}

Vector2 LuaScriptModule::GetPropertyVector2(const Guid & self, const std::string & propertyName)
{
	return m_pKernelModule->GetPropertyVector2(self, propertyName);
}

Vector3 LuaScriptModule::GetPropertyVector3(const Guid & self, const std::string & propertyName)
{
	return m_pKernelModule->GetPropertyVector3(self, propertyName);
}

bool LuaScriptModule::AddClassCallBack(std::string& className, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc)
{
	auto funcNameList = mxClassEventFuncMap.GetElement(className);
	if (!funcNameList)
	{
		funcNameList = new List<string>();
		mxClassEventFuncMap.AddElement(className, funcNameList);

		m_pKernelModule->AddClassCallBack(className, this, &LuaScriptModule::OnClassEventCB);
	}
	
	std::string strfuncName = FindFuncName(luaTable, luaFunc);
	if (!strfuncName.empty())
	{
		if (!funcNameList->Find(strfuncName))
		{
			funcNameList->Add(strfuncName);

			return true;
		}
	}

	return false;
}

int LuaScriptModule::OnClassEventCB(const Guid& objectId, const std::string& className, const CLASS_OBJECT_EVENT classEvent, const DataList& var)
{
    auto funcNameList = mxClassEventFuncMap.GetElement(className);
    if (funcNameList)
    {
		std::string strFuncNme;
		bool ret = funcNameList->First(strFuncNme);
		while (ret)
		{
			try
			{
				LuaIntf::LuaRef func(mLuaContext, strFuncNme.c_str());
				func.call("", objectId, className, (int)classEvent, (DataList)var);
			}
			catch (LuaIntf::LuaException& e)
			{
				cout << e.what() << endl;
				return 0;
			}
			catch (...)
			{
				return 0;
			}

			ret = funcNameList->Next(strFuncNme);
		}
    }

	return -1;
}

void LuaScriptModule::OnScriptReload()
{
    INT64 nAppType = APPType();
    std::string strRootFile = "";
    switch ((SQUICK_SERVER_TYPES)(nAppType))
    {
        case SQUICK_SERVER_TYPES::SQUICK_ST_GAME:
        {
			strRootFile = pPluginManager->GetConfigPath() + "script/game/game_script_reload.lua";
        }
        break;
        case SQUICK_SERVER_TYPES::SQUICK_ST_LOGIN:
        {
			strRootFile = pPluginManager->GetConfigPath() + "script/login/login_script_reload.lua";
        }
        break;
        case SQUICK_SERVER_TYPES::SQUICK_ST_WORLD:
        {
			strRootFile = pPluginManager->GetConfigPath() + "script/world/world_script_reload.lua";
        }
        break;
        case SQUICK_SERVER_TYPES::SQUICK_ST_PROXY:
        {
			strRootFile = pPluginManager->GetConfigPath() + "script/proxy/proxy_script_reload.lua";
        }
        break;
        case SQUICK_SERVER_TYPES::SQUICK_ST_MASTER:
        {
			strRootFile = pPluginManager->GetConfigPath() + "script/master/master_script_reload.lua";
        }
        break;
        default:
        break;
    }
    
    if (!strRootFile.empty())
    {
		TRY_LOAD_SCRIPT_FLE(strRootFile.c_str());
    }
}

bool LuaScriptModule::AddPropertyCallBack(const Guid& self, std::string& propertyName, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc)
{
	std::string luaFuncName = FindFuncName(luaTable, luaFunc);
	if (!luaFuncName.empty())
	{
		if (AddLuaFuncToMap(mxLuaPropertyCallBackFuncMap, self, propertyName, luaFuncName))
		{
			m_pKernelModule->AddPropertyCallBack(self, propertyName, this, &LuaScriptModule::OnLuaPropertyCB);
		}

		return true;
	}
    return false;
}

int LuaScriptModule::OnLuaPropertyCB(const Guid& self, const std::string& propertyName, const NFData& oldVar, const NFData& newVar, const INT64 reason)
{
	auto funcList = mxLuaPropertyCallBackFuncMap.GetElement(propertyName);
	if (funcList)
	{
		auto funcNameList = funcList->GetElement(self);
		if (funcNameList)
		{
			std::string funcName;
			auto Ret = funcNameList->First(funcName);
			while (Ret)
			{
				try
				{
					LuaIntf::LuaRef func(mLuaContext, funcName.c_str());
					func.call("", self, propertyName, oldVar, newVar);
				}
				catch (LuaIntf::LuaException& e)
				{
					cout << e.what() << endl;
				}
				catch (...)
				{
				}

				Ret = funcNameList->Next(funcName);
			}
		}
	}


	return 0;
}

bool LuaScriptModule::AddRecordCallBack(const Guid& self, std::string& recordName, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc)
{
	std::string luaFuncName = FindFuncName(luaTable, luaFunc);
	if (!luaFuncName.empty())
	{
		if (AddLuaFuncToMap(mxLuaRecordCallBackFuncMap, self, recordName, luaFuncName))
		{
			m_pKernelModule->AddRecordCallBack(self, recordName, this, &LuaScriptModule::OnLuaRecordCB);
		}
		return true;
	}

	return false;
}

int LuaScriptModule::OnLuaRecordCB(const Guid& self, const RECORD_EVENT_DATA& eventData, const NFData& oldVar, const NFData& newVar)
{
	auto funcList = mxLuaRecordCallBackFuncMap.GetElement(eventData.recordName);
	if (funcList)
	{
		auto funcNameList = funcList->GetElement(self);
		if (funcNameList)
		{
			std::string funcName;
			auto Ret = funcNameList->First(funcName);
			while (Ret)
			{
				try
				{
					LuaIntf::LuaRef func(mLuaContext, funcName.c_str());
					func.call<LuaIntf::LuaRef>("", self, eventData.recordName, eventData.nOpType, eventData.row, eventData.col, oldVar, newVar);
				}
				catch (LuaIntf::LuaException& e)
				{
					cout << e.what() << endl;
				}
				catch (...)
				{
				}

				Ret = funcNameList->Next(funcName);
			}
		}
	}

    return 0;
}

bool LuaScriptModule::AddEventCallBack(const Guid& self, const int eventID, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc)
{
	std::string luaFuncName = FindFuncName(luaTable, luaFunc);
	if (!luaFuncName.empty())
	{
		if (AddLuaFuncToMap(mxLuaEventCallBackFuncMap, self, (int)eventID, luaFuncName))
		{
			m_pEventModule->AddEventCallBack(self, eventID, this, &LuaScriptModule::OnLuaEventCB);
		}

		return true;
	}

	return false;
}

int LuaScriptModule::OnLuaEventCB(const Guid& self, const int eventID, const DataList& argVar)
{

	auto funcList = mxLuaEventCallBackFuncMap.GetElement(eventID);
	if (funcList)
	{
		auto funcNameList = funcList->GetElement(self);
		if (funcNameList)
		{
			std::string funcName;
			auto Ret = funcNameList->First(funcName);
			while (Ret)
			{
				try
				{
					LuaIntf::LuaRef func(mLuaContext, funcName.c_str());
					func.call<LuaIntf::LuaRef>("", self, eventID, (DataList&)argVar);
				}
				catch (LuaIntf::LuaException& e)
				{
					cout << e.what() << endl;
				}
				catch (...)
				{
				}

				Ret = funcNameList->Next(funcName);
			}
		}
	}

    return 0;
}

bool LuaScriptModule::AddModuleSchedule(std::string& strHeartBeatName, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc, const float time, const int count)
{
	std::string luaFuncName = FindFuncName(luaTable, luaFunc);
	if (!luaFuncName.empty())
	{
		if (AddLuaFuncToMap(mxLuaHeartBeatCallBackFuncMap, strHeartBeatName, luaFuncName))
		{
			return m_pScheduleModule->AddSchedule(Guid(), strHeartBeatName, this, &LuaScriptModule::OnLuaHeartBeatCB, time, count);
		}
	}

	return false;
}

bool LuaScriptModule::AddSchedule(const Guid& self, std::string& strHeartBeatName, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc, const float time, const int count)
{
	std::string luaFuncName = FindFuncName(luaTable, luaFunc);
	if (!luaFuncName.empty())
	{
		if (AddLuaFuncToMap(mxLuaHeartBeatCallBackFuncMap, self, strHeartBeatName, luaFuncName))
		{
			m_pScheduleModule->AddSchedule(self, strHeartBeatName, this, &LuaScriptModule::OnLuaHeartBeatCB, time, count);
		}

		return true;
	}

	return false;
}

int LuaScriptModule::OnLuaHeartBeatCB(const Guid& self, const std::string& strHeartBeatName, const float time, const int count)
{

	auto funcList = mxLuaHeartBeatCallBackFuncMap.GetElement(strHeartBeatName);
	if (funcList)
	{
		auto funcNameList = funcList->GetElement(self);
		if (funcNameList)
		{
			std::string funcName;
			auto Ret = funcNameList->First(funcName);
			while (Ret)
			{
				try
				{
					LuaIntf::LuaRef func(mLuaContext, funcName.c_str());
					if (self.IsNull())
					{
						func.call<LuaIntf::LuaRef>("", strHeartBeatName, time, count);
					}
					else
					{
						func.call<LuaIntf::LuaRef>("", self, strHeartBeatName, time, count);
					}
				}
				catch (LuaIntf::LuaException& e)
				{
					cout << e.what() << endl;
				}
				catch (...)
				{
				}

				Ret = funcNameList->Next(funcName);
			}
		}
	}

    return 0;
}

int LuaScriptModule::AddRow(const Guid& self, std::string& recordName, const DataList& var)
{
    SQUICK_SHARE_PTR<IRecord> pRecord = m_pKernelModule->FindRecord(self, recordName);
    if (nullptr == pRecord)
    {
        return -1;
    }

    return pRecord->AddRow(-1, var);
}

bool LuaScriptModule::RemRow(const Guid & self, std::string & recordName, const int row)
{
    SQUICK_SHARE_PTR<IRecord> pRecord = m_pKernelModule->FindRecord(self, recordName);
    if (nullptr == pRecord)
    {
        return false;
    }

    return pRecord->Remove(row);
}

bool LuaScriptModule::SetRecordInt(const Guid & self, const std::string & recordName, const int row, const std::string & colTag, const INT64 value)
{
	return m_pKernelModule->SetRecordInt(self, recordName, row, colTag, value);
}

bool LuaScriptModule::SetRecordFloat(const Guid & self, const std::string & recordName, const int row, const std::string & colTag, const double value)
{
	return m_pKernelModule->SetRecordFloat(self, recordName, row, colTag, value);
}

bool LuaScriptModule::SetRecordString(const Guid & self, const std::string & recordName, const int row, const std::string & colTag, const std::string & value)
{
	return m_pKernelModule->SetRecordString(self, recordName, row, colTag, value);
}

bool LuaScriptModule::SetRecordObject(const Guid & self, const std::string & recordName, const int row, const std::string & colTag, const Guid & value)
{
	return m_pKernelModule->SetRecordObject(self, recordName, row, colTag, value);
}

bool LuaScriptModule::SetRecordVector2(const Guid & self, const std::string & recordName, const int row, const std::string & colTag, const Vector2 & value)
{
	return m_pKernelModule->SetRecordVector2(self, recordName, row, colTag, value);
}

bool LuaScriptModule::SetRecordVector3(const Guid & self, const std::string & recordName, const int row, const std::string & colTag, const Vector3 & value)
{
	return m_pKernelModule->SetRecordVector3(self, recordName, row, colTag, value);
}

INT64 LuaScriptModule::GetRecordInt(const Guid & self, const std::string & recordName, const int row, const std::string & colTag)
{
	return m_pKernelModule->GetRecordInt(self, recordName, row, colTag);
}

double LuaScriptModule::GetRecordFloat(const Guid & self, const std::string & recordName, const int row, const std::string & colTag)
{
	return m_pKernelModule->GetRecordFloat(self, recordName, row, colTag);
}

std::string LuaScriptModule::GetRecordString(const Guid & self, const std::string & recordName, const int row, const std::string & colTag)
{
	return m_pKernelModule->GetRecordString(self, recordName, row, colTag);
}

Guid LuaScriptModule::GetRecordObject(const Guid & self, const std::string & recordName, const int row, const std::string & colTag)
{
	return m_pKernelModule->GetRecordObject(self, recordName, row, colTag);
}

Vector2 LuaScriptModule::GetRecordVector2(const Guid & self, const std::string & recordName, const int row, const std::string & colTag)
{
	return m_pKernelModule->GetRecordVector2(self, recordName, row, colTag);
}

Vector3 LuaScriptModule::GetRecordVector3(const Guid & self, const std::string & recordName, const int row, const std::string & colTag)
{
	return m_pKernelModule->GetRecordVector3(self, recordName, row, colTag);
}

INT64 LuaScriptModule::GetNowTime()
{
	return pPluginManager->GetNowTime();
}

Guid LuaScriptModule::CreateId()
{
	return m_pKernelModule->CreateGUID();
}

INT64 LuaScriptModule::APPId()
{
	return pPluginManager->GetAppID();
}

INT64 LuaScriptModule::APPType()
{
    SQUICK_SHARE_PTR<IClass> xLogicClass = m_pClassModule->GetElement(SquickProtocol::Server::ThisName());
    if (xLogicClass)
    {
		const std::vector<std::string>& strIdList = xLogicClass->GetIDList();
		for (int i = 0; i < strIdList.size(); ++i)
		{
			const std::string& strId = strIdList[i];

            const int serverType = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::Type());
            const int serverID = m_pElementModule->GetPropertyInt32(strId, SquickProtocol::Server::ServerID());
            if (pPluginManager->GetAppID() == serverID)
            {
                return serverType;
            }
        }
    }
    
	return 0;
}

bool LuaScriptModule::ExistElementObject(const std::string & configName)
{
	return m_pElementModule->ExistElement(configName);
}

std::vector<std::string> LuaScriptModule::GetEleList(const std::string& className)
{
    SQUICK_SHARE_PTR<IClass> xLogicClass = m_pClassModule->GetElement(SquickProtocol::Server::ThisName());
	if (xLogicClass)
	{
		return xLogicClass->GetIDList();
    }

    return std::vector<std::string>();
}

INT64 LuaScriptModule::GetElePropertyInt(const std::string & configName, const std::string & propertyName)
{
	return m_pElementModule->GetPropertyInt(configName, propertyName);
}

double LuaScriptModule::GetElePropertyFloat(const std::string & configName, const std::string & propertyName)
{
	return m_pElementModule->GetPropertyFloat(configName, propertyName);
}

std::string LuaScriptModule::GetElePropertyString(const std::string & configName, const std::string & propertyName)
{
	return m_pElementModule->GetPropertyString(configName, propertyName);
}

Vector2 LuaScriptModule::GetElePropertyVector2(const std::string & configName, const std::string & propertyName)
{
	return m_pElementModule->GetPropertyVector2(configName, propertyName);
}

Vector3 LuaScriptModule::GetElePropertyVector3(const std::string & configName, const std::string & propertyName)
{
	return m_pElementModule->GetPropertyVector3(configName, propertyName);
}

template<typename T>
bool LuaScriptModule::AddLuaFuncToMap(Map<T, Map<Guid, List<string>>>& funcMap, const Guid& self, T key, string& luaFunc)
{
    auto funcList = funcMap.GetElement(key);
    if (!funcList)
    {
        List<string>* funcNameList = new List<string>;
        funcNameList->Add(luaFunc);
        funcList = new Map<Guid, List<string>>;
        funcList->AddElement(self, funcNameList);
        funcMap.AddElement(key, funcList);
        return true;
    }

    if (!funcList->GetElement(self))
    {
        List<string>* funcNameList = new List<string>;
        funcNameList->Add(luaFunc);
        funcList->AddElement(self, funcNameList);
        return true;
    }
    else
    {
        auto funcNameList = funcList->GetElement(self);
        if (!funcNameList->Find(luaFunc))
        {
            funcNameList->Add(luaFunc);
            return true;
        }
        else
        {
            return false;
        }
    }

}


template<typename T>
bool LuaScriptModule::AddLuaFuncToMap(Map<T, Map<Guid, List<string>>>& funcMap, T key, string& luaFunc)
{
    auto funcList = funcMap.GetElement(key);
    if (!funcList)
    {
        List<string>* funcNameList = new List<string>;
        funcNameList->Add(luaFunc);
        funcList = new Map<Guid, List<string>>;
        funcList->AddElement(Guid(), funcNameList);
        funcMap.AddElement(key, funcList);
        return true;
    }

    if (!funcList->GetElement(Guid()))
    {
        List<string>* funcNameList = new List<string>;
        funcNameList->Add(luaFunc);
        funcList->AddElement(Guid(), funcNameList);
        return true;
    }
    else
    {
        auto funcNameList = funcList->GetElement(Guid());
        if (!funcNameList->Find(luaFunc))
        {
            funcNameList->Add(luaFunc);
            return true;
        }
        else
        {
            return false;
        }
    }

}

void LuaScriptModule::RemoveCallBackAsServer(const int msgID)
{
	m_pNetModule->RemoveReceiveCallBack(msgID);
}

void LuaScriptModule::AddMsgCallBackAsServer(const int msgID, const LuaIntf::LuaRef & luaTable, const LuaIntf::LuaRef & luaFunc)
{
	auto funcNameList = mxNetMsgCallBackFuncMapAsServer.GetElement(msgID);
	if (!funcNameList)
	{
		funcNameList = new List<string>();
		mxNetMsgCallBackFuncMapAsServer.AddElement(msgID, funcNameList);

		m_pNetModule->AddReceiveCallBack(msgID, this, &LuaScriptModule::OnNetMsgCallBackAsServer);
	}

	std::string funcName = FindFuncName(luaTable, luaFunc);
	if (!funcName.empty())
	{
		if (!funcNameList->Find(funcName))
		{
			funcNameList->Add(funcName);
		}
	}
}

void LuaScriptModule::RemoveMsgCallBackAsClient(const SQUICK_SERVER_TYPES serverType, const int msgID)
{
	m_pNetClientModule->RemoveReceiveCallBack(serverType, msgID);
}

void LuaScriptModule::AddMsgCallBackAsClient(const SQUICK_SERVER_TYPES serverType, const int msgID, const LuaIntf::LuaRef & luaTable, const LuaIntf::LuaRef & luaFunc)
{
	auto serverMap = mxNetMsgCallBackFuncMapAsClient.GetElement(serverType);
	if (!serverMap)
	{
		serverMap = new Map<int, List<std::string>>();
		mxNetMsgCallBackFuncMapAsClient.AddElement(serverType, serverMap);
	}

	auto funcNameList = serverMap->GetElement(msgID);
	if (!funcNameList)
	{
		funcNameList = new List<string>();
		serverMap->AddElement(msgID, funcNameList);

		switch (serverType)
		{
			case SQUICK_SERVER_TYPES::SQUICK_ST_MASTER:
				m_pNetClientModule->AddReceiveCallBack(serverType, msgID, this, &LuaScriptModule::OnNetMsgCallBackAsClientForMasterServer);
				break;
			case SQUICK_SERVER_TYPES::SQUICK_ST_WORLD:
				m_pNetClientModule->AddReceiveCallBack(serverType, msgID, this, &LuaScriptModule::OnNetMsgCallBackAsClientForWorldServer);
				break;
			case SQUICK_SERVER_TYPES::SQUICK_ST_GAME:
				m_pNetClientModule->AddReceiveCallBack(serverType, msgID, this, &LuaScriptModule::OnNetMsgCallBackAsClientForGameServer);
				break;
			default:
				break;
		}

	}

	std::string funcName = FindFuncName(luaTable, luaFunc);
	if (!funcName.empty())
	{
		if (!funcNameList->Find(funcName))
		{
			funcNameList->Add(funcName);
		}
	}
}

/*
void LuaScriptModule::RemoveHttpCallBack(const std::string & path)
{
}
void LuaScriptModule::AddHttpCallBack(const std::string & path, const int httpType, const LuaIntf::LuaRef & luaTable, const LuaIntf::LuaRef & luaFunc)
{
}
*/

void LuaScriptModule::ImportProtoFile(const std::string& fileName)
{
	LuaPBModule* p = (LuaPBModule*)m_pLuaPBModule;
	p->ImportProtoFile(fileName);
}

const std::string LuaScriptModule::Encode(const std::string& msgTypeName, const LuaIntf::LuaRef& luaTable)
{
	LuaPBModule* p = (LuaPBModule*)m_pLuaPBModule;
	return p->Encode(msgTypeName, luaTable);
}

LuaIntf::LuaRef LuaScriptModule::Decode(const std::string& msgTypeName, const std::string& data)
{
	LuaPBModule* p = (LuaPBModule*)m_pLuaPBModule;
	return p->Decode(msgTypeName, data);
}

void LuaScriptModule::SendToServerByServerID(const int serverID, const uint16_t msgID, const std::string& data)
{
    if (pPluginManager->GetAppID() == serverID)
    {
        m_pLogModule->LogError("you can send message to yourself");
        return;
    }

	m_pNetClientModule->SendByServerID(serverID, msgID, data);
}

void LuaScriptModule::SendToServerBySuit(const SQUICK_SERVER_TYPES eType, const uint16_t msgID, const std::string & data, const std::string& hash)
{
	m_pNetClientModule->SendBySuitWithOutHead(eType, hash, msgID,data );
}

void LuaScriptModule::SendToAllServerByServerType(const SQUICK_SERVER_TYPES eType, const uint16_t msgID, const std::string &data)
{
	m_pNetClientModule->SendToAllServer(eType, msgID,data );
}

void LuaScriptModule::SendMsgToClientByFD(const NFSOCK fd, const uint16_t msgID, const std::string &data)
{
	//for all servers
	m_pNetModule->SendMsgWithOutHead(msgID, data, fd);
}

void LuaScriptModule::SendMsgToPlayer(const Guid player, const uint16_t msgID, const std::string& data)
{
    //the app must be the game server
	if (pPluginManager->GetAppType() == SQUICK_SERVER_TYPES::SQUICK_ST_GAME)
	{

	}
	else if (pPluginManager->GetAppType() == SQUICK_SERVER_TYPES::SQUICK_ST_WORLD)
	{

	}
	else if (pPluginManager->GetAppType() == SQUICK_SERVER_TYPES::SQUICK_ST_PROXY)
	{
	}
	else
	{
		m_pLogModule->LogError("you are not: SQUICK_ST_GAME || SQUICK_ST_WORLD");
	}
}

void LuaScriptModule::SendToGroupPlayer(const uint16_t msgID, const std::string& data)
{
    //the app must be the game server
	if (pPluginManager->GetAppType() == SQUICK_SERVER_TYPES::SQUICK_ST_GAME)
	{

	}
	else
	{
		m_pLogModule->LogError("you are not an game server");
	}
}

void LuaScriptModule::SendToAllPlayer(const uint16_t msgID, const std::string& data)
{
	//if game server
	//if world server
	//if proxy server
	if (pPluginManager->GetAppType() == SQUICK_SERVER_TYPES::SQUICK_ST_GAME)
	{
	}
	else if (pPluginManager->GetAppType() == SQUICK_SERVER_TYPES::SQUICK_ST_WORLD)
	{
	}
	else if (pPluginManager->GetAppType() == SQUICK_SERVER_TYPES::SQUICK_ST_PROXY)
	{
		m_pNetModule->SendMsgToAllClientWithOutHead(msgID, data);
	}
	else
	{
		m_pLogModule->LogError("you are not an game server or world server");
	}
}

void LuaScriptModule::LogInfo(const std::string& logData)
{
	m_pLogModule->LogInfo(logData);
}

void LuaScriptModule::LogError(const std::string& logData)
{
	m_pLogModule->LogError(logData);
}

void LuaScriptModule::LogWarning(const std::string& logData)
{
	m_pLogModule->LogWarning(logData);
}

void LuaScriptModule::LogDebug(const std::string& logData)
{
	m_pLogModule->LogDebug(logData);
}

void LuaScriptModule::SetVersionCode(const std::string& logData)
{
    strVersionCode = logData;
}

const std::string&  LuaScriptModule::GetVersionCode()
{
    return strVersionCode;
}

bool LuaScriptModule::Register()
{

	LuaIntf::LuaBinding(mLuaContext).beginClass<Guid>("Guid")
		.addConstructor(LUA_ARGS())
		.addProperty("data", &Guid::GetData, &Guid::SetData)
		.addProperty("head", &Guid::GetHead, &Guid::SetHead)
		.addFunction("tostring", &Guid::ToString)
		.addFunction("fromstring", &Guid::FromString)
		.endClass();

	LuaIntf::LuaBinding(mLuaContext).beginClass<DataList>("DataList")
		.endClass();

	LuaIntf::LuaBinding(mLuaContext).beginExtendClass<DataList, DataList>("DataList")
		.addConstructor(LUA_ARGS())
		.addFunction("empty", &DataList::IsEmpty)
		.addFunction("count", &DataList::GetCount)
		.addFunction("tye", &DataList::Type)

		.addFunction("add_int", &DataList::AddInt)
		.addFunction("add_float", &DataList::AddFloat)
		.addFunction("add_string", &DataList::AddStringFromChar)
		.addFunction("add_object", &DataList::AddObject)
		.addFunction("add_vector2", &DataList::AddVector2)
		.addFunction("add_vector3", &DataList::AddVector3)

		.addFunction("set_int", &DataList::SetInt)
		.addFunction("set_float", &DataList::SetFloat)
		.addFunction("set_string", &DataList::SetString)
		.addFunction("set_object", &DataList::SetObject)
		.addFunction("set_vector2", &DataList::SetVector2)
		.addFunction("set_vector3", &DataList::SetVector3)

		.addFunction("int", &DataList::Int)
		.addFunction("float", &DataList::Float)
		.addFunction("string", &DataList::String)
		.addFunction("object", &DataList::Object)
		.addFunction("vector2", &DataList::Vector2At)
		.addFunction("vector3", &DataList::Vector3At)
		.endClass();

	LuaIntf::LuaBinding(mLuaContext).beginClass<NFData>("TData")
		.addConstructor(LUA_ARGS())
		.addFunction("float", &NFData::GetFloat)
		.addFunction("int", &NFData::GetInt)
		.addFunction("object", &NFData::GetObject)
		.addFunction("string", &NFData::GetString)
		.addFunction("vector2", &NFData::GetVector2)
		.addFunction("vector3", &NFData::GetVector3)

		.addFunction("type", &NFData::GetType)
		.addFunction("is_null", &NFData::IsNullValue)

		.addFunction("set_float", &NFData::SetFloat)
		.addFunction("set_int", &NFData::SetInt)
		.addFunction("set_object", &NFData::SetObject)
		.addFunction("set_string", &NFData::SetString)
		.addFunction("set_vector2", &NFData::SetVector2)
		.addFunction("set_vector3", &NFData::SetVector3)
		.endClass();

	//for kernel module
	LuaIntf::LuaBinding(mLuaContext).beginClass<LuaScriptModule>("LuaScriptModule")
		.addFunction("register_module", &LuaScriptModule::RegisterModule)
		.addFunction("create_object", &LuaScriptModule::CreateObject)
		.addFunction("exist_object", &LuaScriptModule::ExistObject)
		.addFunction("destroy_object", &LuaScriptModule::DestroyObject)
		.addFunction("enter_scene", &LuaScriptModule::EnterScene)
		.addFunction("do_event", &LuaScriptModule::DoEvent)

		.addFunction("set_prop_int", &LuaScriptModule::SetPropertyInt)
		.addFunction("set_prop_float", &LuaScriptModule::SetPropertyFloat)
		.addFunction("set_prop_string", &LuaScriptModule::SetPropertyString)
		.addFunction("set_prop_object", &LuaScriptModule::SetPropertyObject)
		.addFunction("set_prop_vector2", &LuaScriptModule::SetPropertyVector2)
		.addFunction("set_prop_vector3", &LuaScriptModule::SetPropertyVector3)


		.addFunction("get_prop_int", &LuaScriptModule::GetPropertyInt)
		.addFunction("get_prop_float", &LuaScriptModule::GetPropertyFloat)
		.addFunction("get_prop_string", &LuaScriptModule::GetPropertyString)
		.addFunction("get_prop_object", &LuaScriptModule::GetPropertyObject)
		.addFunction("get_prop_vector2", &LuaScriptModule::GetPropertyVector2)
		.addFunction("get_prop_vector3", &LuaScriptModule::GetPropertyVector3)

		.addFunction("set_record_int", &LuaScriptModule::SetRecordInt)
		.addFunction("set_record_float",&LuaScriptModule::SetRecordFloat)
		.addFunction("set_record_string", &LuaScriptModule::SetRecordString)
		.addFunction("set_record_object", &LuaScriptModule::SetRecordObject)
		.addFunction("set_record_vector2", &LuaScriptModule::SetPropertyVector2)
		.addFunction("set_record_vector3", &LuaScriptModule::SetPropertyVector3)

		.addFunction("get_record_int", &LuaScriptModule::GetRecordInt)
		.addFunction("get_record_float", &LuaScriptModule::GetRecordFloat)
		.addFunction("get_record_string", &LuaScriptModule::GetRecordString)
		.addFunction("get_record_object", &LuaScriptModule::GetRecordObject)
		.addFunction("get_record_vector2", &LuaScriptModule::GetPropertyVector2)
		.addFunction("get_record_vector3", &LuaScriptModule::GetPropertyVector3)

		.addFunction("add_prop_cb", &LuaScriptModule::AddPropertyCallBack)
		.addFunction("add_record_cb", &LuaScriptModule::AddRecordCallBack)
		.addFunction("add_event_cb", &LuaScriptModule::AddEventCallBack)
		.addFunction("add_class_cb", &LuaScriptModule::AddClassCallBack)
		.addFunction("add_schedule", &LuaScriptModule::AddSchedule)
		.addFunction("add_module_schedule", &LuaScriptModule::AddModuleSchedule)
		.addFunction("do_event", &LuaScriptModule::DoEvent)
		.addFunction("add_row", &LuaScriptModule::AddRow)
		.addFunction("rem_row", &LuaScriptModule::RemRow)

		.addFunction("time", &LuaScriptModule::GetNowTime)
		.addFunction("new_id", &LuaScriptModule::CreateId)
		.addFunction("app_id", &LuaScriptModule::APPId)
		.addFunction("app_type", &LuaScriptModule::APPType)

		.addFunction("exist_ele", &LuaScriptModule::ExistElementObject)
		.addFunction("get_ele_list", &LuaScriptModule::GetEleList)
		.addFunction("get_ele_int", &LuaScriptModule::GetElePropertyInt)
		.addFunction("get_ele_float", &LuaScriptModule::GetElePropertyFloat)
		.addFunction("get_ele_string", &LuaScriptModule::GetElePropertyString)
		.addFunction("get_ele_vector2", &LuaScriptModule::GetElePropertyVector2)
		.addFunction("get_ele_vector3", &LuaScriptModule::GetElePropertyVector3)

		.addFunction("remove_msg_cb_as_server", &LuaScriptModule::RemoveCallBackAsServer)//as server
		.addFunction("add_msg_cb_as_server", &LuaScriptModule::AddMsgCallBackAsServer)//as server
		.addFunction("remove_msg_cb_as_client", &LuaScriptModule::RemoveMsgCallBackAsClient)//as client
		.addFunction("add_msg_cb_as_client", &LuaScriptModule::AddMsgCallBackAsClient)//as client

		//.addFunction("remove_http_cb", &LuaScriptModule::RemoveHttpCallBack)
		//.addFunction("add_http_cb", &LuaScriptModule::AddHttpCallBack)

		.addFunction("send_to_server_by_id", &LuaScriptModule::SendToServerByServerID)//as client
		.addFunction("send_to_all_server_by_type", &LuaScriptModule::SendToAllServerByServerType)//as client
		.addFunction("send_to_server_by_suit", &LuaScriptModule::SendToServerBySuit)//as client

		.addFunction("send_to_client_by_fd", &LuaScriptModule::SendMsgToClientByFD)//as server

		.addFunction("send_to_player", &LuaScriptModule::SendMsgToPlayer)//as game server
		.addFunction("send_to_group_player", &LuaScriptModule::SendToGroupPlayer)//as game server
		.addFunction("send_to_all_player", &LuaScriptModule::SendToAllPlayer)//as game server

		.addFunction("log_info", &LuaScriptModule::LogInfo)
		.addFunction("log_error", &LuaScriptModule::LogError)
		.addFunction("log_warning", &LuaScriptModule::LogWarning)
		.addFunction("log_debug", &LuaScriptModule::LogDebug)

		.addFunction("get_version_code", &LuaScriptModule::GetVersionCode)
		.addFunction("set_version_code", &LuaScriptModule::SetVersionCode)

		.addFunction("import_proto_file", &LuaScriptModule::ImportProtoFile)
		.addFunction("encode", &LuaScriptModule::Encode)
		.addFunction("decode", &LuaScriptModule::Decode)

		.endClass();

    return true;
}

std::string LuaScriptModule::FindFuncName(const LuaIntf::LuaRef & luaTable, const LuaIntf::LuaRef & luaFunc)
{
	if (luaTable.isTable() && luaFunc.isFunction())
	{
		std::string strLuaTableName = "";
		std::map<std::string, LuaIntf::LuaRef>::iterator it = mxTableName.begin();
		for (it; it != mxTableName.end(); ++it)
		{
			if (it->second == luaTable)
			{
				strLuaTableName = it->first;
			}
		}
		
		if (!strLuaTableName.empty())
		{
			for (auto itr = luaTable.begin(); itr != luaTable.end(); ++itr)
			{
				const LuaIntf::LuaRef& key = itr.key();

				const std::string& sKey = key.toValue<std::string>();
				const LuaIntf::LuaRef& val = itr.value();
				if (val.isFunction() && luaFunc.isFunction() && val == luaFunc)
				{
					strLuaTableName.append(".");
					strLuaTableName.append(sKey);
					return strLuaTableName;
				}
			}
		}
	}

	return NULL_STR;
}

void LuaScriptModule::OnNetMsgCallBackAsServer(const NFSOCK sockIndex, const int msgID, const char *msg, const uint32_t len)
{
	auto msgCallBack = mxNetMsgCallBackFuncMapAsServer.GetElement(msgID);
	if (msgCallBack)
	{
		std::string msgData(msg, len);
		std::string funcName;
		auto Ret = msgCallBack->First(funcName);
		while (Ret)
		{
			try
			{
				LuaIntf::LuaRef func(mLuaContext, funcName.c_str());
				func.call<LuaIntf::LuaRef>("", sockIndex, msgID, msgData);
			}
			catch (LuaIntf::LuaException& e)
			{
				cout << e.what() << endl;
			}
			catch (...)
			{
			}

			Ret = msgCallBack->Next(funcName);
		}
	}
}

void LuaScriptModule::OnNetMsgCallBackAsClientForMasterServer(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	auto serverData = mxNetMsgCallBackFuncMapAsClient.GetElement(SQUICK_SERVER_TYPES::SQUICK_ST_MASTER);
	if (serverData)
	{
		auto msgCallBack = serverData->GetElement(msgID);
		if (msgCallBack)
		{
			std::string msgData(msg, len);

			std::string funcName;
			auto Ret = msgCallBack->First(funcName);
			while (Ret)
			{
				try
				{
					LuaIntf::LuaRef func(mLuaContext, funcName.c_str());
					func.call<LuaIntf::LuaRef>("", sockIndex, msgID, msgData);
				}
				catch (LuaIntf::LuaException& e)
				{
					cout << e.what() << endl;
				}
				catch (...)
				{
				}

				Ret = msgCallBack->Next(funcName);
			}
		}
	}
}

void LuaScriptModule::OnNetMsgCallBackAsClientForWorldServer(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	auto serverData = mxNetMsgCallBackFuncMapAsClient.GetElement(SQUICK_SERVER_TYPES::SQUICK_ST_WORLD);
	if (serverData)
	{
		auto msgCallBack = serverData->GetElement(msgID);
		if (msgCallBack)
		{
			std::string msgData(msg, len);

			std::string funcName;
			auto Ret = msgCallBack->First(funcName);
			while (Ret)
			{
				try
				{
					LuaIntf::LuaRef func(mLuaContext, funcName.c_str());
					func.call<LuaIntf::LuaRef>("", sockIndex, msgID, msgData);
				}
				catch (LuaIntf::LuaException& e)
				{
					cout << e.what() << endl;
				}
				catch (...)
				{
				}

				Ret = msgCallBack->Next(funcName);
			}
		}
	}
}

void LuaScriptModule::OnNetMsgCallBackAsClientForGameServer(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len)
{
	auto serverData = mxNetMsgCallBackFuncMapAsClient.GetElement(SQUICK_SERVER_TYPES::SQUICK_ST_GAME);
	if (serverData)
	{
		auto msgCallBack = serverData->GetElement(msgID);
		if (msgCallBack)
		{
			std::string msgData(msg, len);

			std::string funcName;
			auto Ret = msgCallBack->First(funcName);
			while (Ret)
			{
				try
				{
					LuaIntf::LuaRef func(mLuaContext, funcName.c_str());
					func.call<LuaIntf::LuaRef>("", sockIndex, msgID, msgData);
				}
				catch (LuaIntf::LuaException& e)
				{
					cout << e.what() << endl;
				}
				catch (...)
				{
				}

				Ret = msgCallBack->Next(funcName);
			}
		}
	}
}