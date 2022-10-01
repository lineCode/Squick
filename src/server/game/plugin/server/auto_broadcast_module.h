

#ifndef SQUICK_AUTO_BROADCAST_MODULE_H
#define SQUICK_AUTO_BROADCAST_MODULE_H

#include <memory>
#include "squick/struct/struct.h"
#include "squick/base/net.h"
#include "squick/base/log.h"
#include "squick/base/kernel.h"
#include "squick/base/class.h"

#include "squick/base/element.h"
#include "squick/base/event.h"
#include "squick/base/scene.h"


#include "if_auto_broadcast_module.h"
#include "../logic/if_scene_process_module.h"
#include "../client/if_world_module.h"
#include "../server/if_server_module.h"

////////////////////////////////////////////////////////////////////////////



class AutoBroadcastModule
    : public IAutoBroadcastModule
{
public:
	AutoBroadcastModule(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();
    virtual bool AfterInit();

private:
	int OnObjectClassEvent(const Guid& self, const std::string& className, const CLASS_OBJECT_EVENT classEvent, const DataList& var);

	int OnSceneEvent(const Guid & self, const int sceneID, const int groupID, const int type, const DataList& argList);

	//broad the data of argvar to self
	int OnObjectListEnter(const DataList& self, const DataList& argVar);
	int OnObjectDataFinished(const DataList& self, const DataList& argVar);
	int OnObjectListLeave(const DataList& self, const DataList& argVar);

	//broad the data of self to argvar 
	int OnPropertyEnter(const DataList& argVar, const Guid& self);
	int OnRecordEnter(const DataList& argVar, const Guid& self);

	int OnPropertyEvent(const Guid& self, const std::string& propertyName, const NFData& oldVar, const NFData& newVar, const DataList& argVar, const INT64 reason);
	int OnRecordEvent(const Guid& self, const std::string& recordName, const RECORD_EVENT_DATA& eventData, const NFData& oldVar, const NFData& newVar, const DataList& argVar);


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
