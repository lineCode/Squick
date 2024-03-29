

#ifndef SQUICK_LUA_SCRIPT_MODULE_H
#define SQUICK_LUA_SCRIPT_MODULE_H

#ifdef min
#undef min
#endif

//just define it as 0 if you want to use luaintf with C
//#define LUAINTF_LINK_LUA_COMPILED_IN_CXX 0

#include "squick/base/net.h"
#include "squick/base/kernel.h"
#include "squick/base/class.h"
#include "squick/base/event.h"
#include "squick/base/schedule.h"
#include "squick/base/element.h"
#include "squick/base/net_client.h"
#include "squick/base/log.h"
#include "lua_pb_module.h"
/*
void call0(lua_State* lua_state,const char* name)
{
	lua_getglobal(lua_state, name);
	if (lua_isfunction(lua_state, -1))
	{
		lua_pcall(lua_state, 0, 0, 0);
	}
}
template<typename T1>
void call1(lua_State* lua_state,const char* name, T1 arg1)
{
	lua_getglobal(lua_state, name);
	if (lua_isfunction(lua_state, -1))
	{
		luabridge::Stack<T1>::push(lua_state, arg1);
		lua_pcall(lua_state, 1, 0, 0);
	}
}
template<typename T1, typename T2>
void call2(lua_State* lua_state,const char* name, T1 arg1, T2 arg2)
{
	lua_getglobal(lua_state, name);
	if (lua_isfunction(lua_state, -1))
	{
		luabridge::Stack<T1>::push(lua_state, arg1);
		luabridge::Stack<T2>::push(lua_state, arg2);
		lua_pcall(lua_state, 2, 0, 0);
	}
}
*/

class ILuaScriptModule
		: public IModule
{
public:

};

class LuaScriptModule
    : public ILuaScriptModule
{
public:
    LuaScriptModule(IPluginManager* p)
    {
        m_bIsExecute = true;
        pPluginManager = p;
    }

	virtual bool Awake();
	virtual bool Init();
    virtual bool Shut();
	virtual bool ReadyExecute();
	virtual bool Execute();

    virtual bool AfterInit();
    virtual bool BeforeShut();


protected:
	void RegisterModule(const std::string& tableName, const LuaIntf::LuaRef& luaTable);

	//FOR KERNEL MODULE
	Guid CreateObject(const Guid& self, const int sceneID, const int groupID, const std::string& className, const std::string& objectIndex, const DataList& arg);
	bool ExistObject(const Guid& self);
	bool DestroyObject(const Guid & self);

	//return the group id
	bool EnterScene(const int sceneID, const int groupID);
	bool DoEvent(const Guid& self, const int eventID, const DataList& arg);

	bool FindProperty(const Guid& self, const std::string& propertyName);

	bool SetPropertyInt(const Guid& self, const std::string& propertyName, const INT64 propValue);
	bool SetPropertyFloat(const Guid& self, const std::string& propertyName, const double propValue);
	bool SetPropertyString(const Guid& self, const std::string& propertyName, const std::string& propValue);
	bool SetPropertyObject(const Guid& self, const std::string& propertyName, const Guid& propValue);
	bool SetPropertyVector2(const Guid& self, const std::string& propertyName, const Vector2& propValue);
	bool SetPropertyVector3(const Guid& self, const std::string& propertyName, const Vector3& propValue);

	INT64 GetPropertyInt(const Guid& self, const std::string& propertyName);
	int GetPropertyInt32(const Guid& self, const std::string& propertyName);	//equal to (int)GetPropertyInt(...), to remove C4244 warning
	double GetPropertyFloat(const Guid& self, const std::string& propertyName);
	std::string GetPropertyString(const Guid& self, const std::string& propertyName);
	Guid GetPropertyObject(const Guid& self, const std::string& propertyName);
	Vector2 GetPropertyVector2(const Guid& self, const std::string& propertyName);
	Vector3 GetPropertyVector3(const Guid& self, const std::string& propertyName);

	bool AddPropertyCallBack(const Guid& self, std::string& propertyName, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc);
    bool AddRecordCallBack(const Guid& self, std::string& recordName, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc);
    bool AddEventCallBack(const Guid& self, const int eventID, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc);
	bool AddSchedule(const Guid& self, std::string& strHeartBeatName, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc, const float time, const int count);
	bool AddModuleSchedule(std::string& strHeartBeatName, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc, const float time, const int count);

	int AddRow(const Guid& self, std::string& recordName, const DataList& var);
	bool RemRow(const Guid& self, std::string& recordName, const int row);

	bool SetRecordInt(const Guid& self, const std::string& recordName, const int row, const std::string& colTag, const INT64 value);
	bool SetRecordFloat(const Guid& self, const std::string& recordName, const int row, const std::string& colTag, const double value);
	bool SetRecordString(const Guid& self, const std::string& recordName, const int row, const std::string& colTag, const std::string& value);
	bool SetRecordObject(const Guid& self, const std::string& recordName, const int row, const std::string& colTag, const Guid& value);
	bool SetRecordVector2(const Guid& self, const std::string& recordName, const int row, const std::string& colTag, const Vector2& value);
	bool SetRecordVector3(const Guid& self, const std::string& recordName, const int row, const std::string& colTag, const Vector3& value);

	INT64 GetRecordInt(const Guid& self, const std::string& recordName, const int row, const std::string& colTag);
	double GetRecordFloat(const Guid& self, const std::string& recordName, const int row, const std::string& colTag);
	std::string GetRecordString(const Guid& self, const std::string& recordName, const int row, const std::string& colTag);
	Guid GetRecordObject(const Guid& self, const std::string& recordName, const int row, const std::string& colTag);
	Vector2 GetRecordVector2(const Guid& self, const std::string& recordName, const int row, const std::string& colTag);
	Vector3 GetRecordVector3(const Guid& self, const std::string& recordName, const int row, const std::string& colTag);

	INT64 GetNowTime();
	Guid CreateId();
	INT64 APPId();
	INT64 APPType();

	//FOR ELEMENT MODULE
	bool ExistElementObject(const std::string& configName);
	std::vector<std::string> GetEleList(const std::string& className);

	INT64 GetElePropertyInt(const std::string& configName, const std::string& propertyName);
	double GetElePropertyFloat(const std::string& configName, const std::string& propertyName);
	std::string GetElePropertyString(const std::string& configName, const std::string& propertyName);
	Vector2 GetElePropertyVector2(const std::string& configName, const std::string& propertyName);
	Vector3 GetElePropertyVector3(const std::string& configName, const std::string& propertyName);

	//FOR NET MODULE
	//as server
	void RemoveCallBackAsServer(const int msgID);
	void AddMsgCallBackAsServer(const int msgID, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc);

	//as client
	void RemoveMsgCallBackAsClient(const SQUICK_SERVER_TYPES serverType, const int msgID);
	void AddMsgCallBackAsClient(const SQUICK_SERVER_TYPES serverType, const int msgID, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc);

/*
	void RemoveHttpCallBack(const std::string& path);
	void AddHttpCallBack(const std::string& path, const int httpType, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc);
*/

    void ImportProtoFile(const std::string& fileName);
    const std::string Encode(const std::string& msgTypeName, const LuaIntf::LuaRef& luaTable);
	LuaIntf::LuaRef Decode(const std::string& msgTypeName, const std::string& data);

	void SendToServerByServerID(const int serverID, const uint16_t msgID, const std::string& data);
	void SendToServerBySuit(const SQUICK_SERVER_TYPES eType, const uint16_t msgID, const std::string& data, const std::string& hash);
	void SendToAllServerByServerType(const SQUICK_SERVER_TYPES eType, const uint16_t msgID, const std::string& data);

    //for net module
	void SendMsgToClientByFD(const NFSOCK fd, const uint16_t msgID, const std::string& data);

	void SendMsgToPlayer(const Guid player, const uint16_t msgID, const std::string& data);
	void SendToAllPlayer(const uint16_t msgID, const std::string& data);
    void SendToGroupPlayer(const uint16_t msgID, const std::string& data);

	//for log
	void LogInfo(const std::string& logData);
	void LogError(const std::string& logData);
	void LogWarning(const std::string& logData);
	void LogDebug(const std::string& logData);

    //hot fix
	void SetVersionCode(const std::string& logData);
	const std::string& GetVersionCode();

	//FOR CLASS MODULE
    bool AddClassCallBack(std::string& className, const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc);

protected:
    template<typename T>
    bool AddLuaFuncToMap(Map<T, Map<Guid, List<string>>>& funcMap, const Guid& self, T key, std::string& luaFunc);

    template<typename T>
    bool AddLuaFuncToMap(Map<T, Map<Guid, List<string>>>& funcMap, T key, std::string& luaFunc);

    int OnLuaPropertyCB(const Guid& self, const std::string& propertyName, const NFData& oldVar, const NFData& newVar, const INT64 reason);
    int OnLuaRecordCB(const Guid& self, const RECORD_EVENT_DATA& eventData, const NFData& oldVar, const NFData& newVar);
    int OnLuaHeartBeatCB(const Guid& self, const std::string& strHeartBeatName, const float time, const int count);

    int OnLuaEventCB(const Guid& self, const int eventID, const DataList& argVar);

    int OnClassEventCB(const Guid& self, const std::string& className, const CLASS_OBJECT_EVENT classEvent, const DataList& var);
    
	void OnScriptReload();

	void OnNetMsgCallBackAsServer(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnNetMsgCallBackAsClientForMasterServer(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnNetMsgCallBackAsClientForWorldServer(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnNetMsgCallBackAsClientForGameServer(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

protected:
    bool Register();
	std::string FindFuncName(const LuaIntf::LuaRef& luaTable, const LuaIntf::LuaRef& luaFunc);


protected:
    IElementModule* m_pElementModule;
    IKernelModule* m_pKernelModule;
    IClassModule* m_pClassModule;
	IEventModule* m_pEventModule;
    NFIScheduleModule* m_pScheduleModule;
    INetClientModule* m_pNetClientModule;
    INetModule* m_pNetModule;
    ILogModule* m_pLogModule;
	ILuaPBModule* m_pLuaPBModule;
	
protected:
    int64_t mnTime;
    std::string strVersionCode;
    LuaIntf::LuaContext mLuaContext;

	std::map<std::string, LuaIntf::LuaRef> mxTableName;

    Map<std::string, Map<Guid, List<std::string>>> mxLuaPropertyCallBackFuncMap;
    Map<std::string, Map<Guid, List<std::string>>> mxLuaRecordCallBackFuncMap;
    Map<int, Map<Guid, List<std::string>>> mxLuaEventCallBackFuncMap;
    Map<std::string, Map<Guid, List<std::string>>> mxLuaHeartBeatCallBackFuncMap;

    Map<std::string, List<std::string>> mxClassEventFuncMap;


	Map<int, List<std::string>> mxNetMsgCallBackFuncMapAsServer;
	Map<SQUICK_SERVER_TYPES, Map<int, List<std::string>>> mxNetMsgCallBackFuncMapAsClient;
};

#endif