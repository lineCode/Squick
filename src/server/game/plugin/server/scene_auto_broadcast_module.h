

#ifndef SQUICK_SCENE_AUTO_BROADCAST_MODULE_H
#define SQUICK_SCENE_AUTO_BROADCAST_MODULE_H

#include <memory>
#include "squick/struct/struct.h"
#include "squick/base/net.h"
#include "squick/base/log.h"
#include "squick/base/kernel.h"
#include "squick/base/class.h"

#include "squick/base/element.h"
#include "squick/base/event.h"
#include "squick/base/scene.h"

#include "../logic/if_scene_process_module.h"
#include "../client/if_world_module.h"
#include "if_server_module.h"
#include "if_scene_auto_broadcast_module.h"
////////////////////////////////////////////////////////////////////////////

class SceneAutoBroadcastModule
    : public ISceneAutoBroadcastModule
{
public:
	SceneAutoBroadcastModule(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();
    virtual bool AfterInit();

private:
	int ClearProperty(const Guid& self, const int sceneID, const int groupID);
	int ClearRecord(const Guid& self, const int sceneID, const int groupID);

	int OnPropertyEvent(const Guid& self, const std::string& propertyName, const NFData& oldVar, const NFData& newVar);
	int OnRecordEvent(const Guid& self, const RECORD_EVENT_DATA& eventData, const NFData& oldVar, const NFData& newVar);

	int OnBeforeLeaveSceneEvent(const Guid & self, const int sceneID, const int groupID, const int type, const DataList& argList);
	int OnAfterEntrySceneEvent(const Guid & self, const int sceneID, const int groupID, const int type, const DataList& argList);
	
	//broad the data of self to argvar 
	int OnPropertyEnter(const DataList& argVar, const int sceneID, const int groupID);
	int OnRecordEnter(const DataList& argVar, const int sceneID, const int groupID);

private:

    IKernelModule* m_pKernelModule;
    IClassModule* m_pClassModule;
    ILogModule* m_pLogModule;
    ISceneProcessModule* m_pSceneProcessModule;
    IElementModule* m_pElementModule;
	INetModule* m_pNetModule;
	IEventModule* m_pEventModule;
	ISceneModule* m_pSceneModule;
    INetClientModule* m_pNetClientModule;
	IGameServerNet_ServerModule* m_pGameServerNet_ServerModule;
};
#endif
