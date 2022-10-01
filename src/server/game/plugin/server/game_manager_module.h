

#ifndef NFGAMEMANAGERMODULE_H
#define NFGAMEMANAGERMODULE_H

#include <memory>
#include "squick/struct/struct.h"
#include "squick/base/net.h"
#include "squick/base/log.h"
#include "squick/base/kernel.h"
#include "squick/base/class.h"

#include "squick/base/element.h"
#include "squick/base/event.h"
#include "squick/base/scene.h"


#include "squick/base/schedule.h"
#include "squick/base/thread_pool.h"

#include "if_game_manager_module.h"
#include "../client/if_world_module.h"
#include "../logic/if_scene_process_module.h"
#include "if_server_module.h"
class GameManagerModule
		: public IGameManagerModule
{
public:
	GameManagerModule(IPluginManager* p)
	{
		pPluginManager = p;
	}

	virtual bool Init();
	virtual bool Shut();
	virtual bool Execute();
	virtual bool AfterInit();

protected:
	void OnClientPropertyIntProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientPropertyFloatProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientPropertyStringProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientPropertyObjectProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientPropertyVector2Process(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientPropertyVector3Process(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

	void OnClientAddRowProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientRemoveRowProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientSwapRowProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientRecordIntProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientRecordFloatProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientRecordStringProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientRecordObjectProcess(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientRecordVector2Process(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);
	void OnClientRecordVector3Process(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

protected:
	//get GM Level and what you want to modify
	std::shared_ptr<IProperty> CalProperty(SQUICK_SHARE_PTR<IObject> pObject, const Guid objectID, const std::string& propertyName, int& gmLevel);
	std::shared_ptr<IRecord> CalRecord(SQUICK_SHARE_PTR<IObject> pObject, const Guid objectID, const std::string& recordName, int& gmLevel);

private:

	//////////////////////////////////////////////////////////////////////////
	IKernelModule* m_pKernelModule;
	IClassModule* m_pClassModule;
	ILogModule* m_pLogModule;
	ISceneProcessModule* m_pSceneProcessModule;
	IElementModule* m_pElementModule;
	INetModule* m_pNetModule;
	IEventModule* m_pEventModule;
	ISceneModule* m_pSceneModule;
	INetClientModule* m_pNetClientModule;
	NFIScheduleModule* m_pScheduleModule;
	IGameServerNet_ServerModule* m_pGameServerNet_ServerModule;
};

#endif