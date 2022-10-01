


#ifndef SQUICK_SCENEPROCESS_MODULE_H
#define SQUICK_SCENEPROCESS_MODULE_H

#include <string>
#include <map>
#include <iostream>
#include "squick/core/map.h"
#include "squick/core/list.h"
#include "third_party/RapidXML/rapidxml.hpp"
#include "third_party/RapidXML/rapidxml_iterators.hpp"
#include "third_party/RapidXML/rapidxml_print.hpp"
#include "third_party/RapidXML/rapidxml_utils.hpp"
#include "squick/struct/protocol_define.h"
#include "squick/base/kernel.h"
#include "squick/base/element.h"
#include "squick/base/class.h"
#include "squick/base/log.h"
#include "squick/base/plugin_manager.h"
#include "squick/base/event.h"
#include "squick/base/scene.h"
#include "squick/base/cell.h"


#include "if_property_module.h"
#include "if_scene_process_module.h"
#include "../server/if_server_module.h"

class SceneProcessModule
    : public ISceneProcessModule
{
public:
    SceneProcessModule(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual ~SceneProcessModule() {};

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();
    virtual bool AfterInit();
	virtual bool ReadyExecute();

	virtual bool RequestEnterScene(const Guid& self, const int sceneID, const int groupID, const int type, const Vector3& pos, const DataList& argList);

protected:
	bool LoadSceneResource(const std::string& strSceneIDName);
	bool CreateSceneBaseGroup(const std::string& strSceneIDName);

protected:

    int OnObjectClassEvent(const Guid& self, const std::string& className, const CLASS_OBJECT_EVENT classEvent, const DataList& var);
	
	int EnterSceneConditionEvent(const Guid& self, const int sceneID, const int groupID, const int type, const DataList& argList);
	
	int BeforeEnterSceneGroupEvent(const Guid& self, const int sceneID, const int groupID, const int type, const DataList& argList);
	int AfterEnterSceneGroupEvent(const Guid& self, const int sceneID, const int groupID, const int type, const DataList& argList);
	int BeforeLeaveSceneGroupEvent(const Guid& self, const int sceneID, const int groupID, const int type, const DataList& argList);
	int AfterLeaveSceneGroupEvent(const Guid& self, const int sceneID, const int groupID, const int type, const DataList& argList);

private:

    IElementModule* m_pElementModule;
    IClassModule* m_pClassModule;
    IKernelModule* m_pKernelModule;
    ILogModule* m_pLogModule;
	IEventModule* m_pEventModule;
	ISceneModule* m_pSceneModule;
	NFICellModule* m_pCellModule;
    IGameServerNet_ServerModule* m_pGameServerNet_ServerModule;
};

#endif
