

#ifndef SQUICK_DATA_TRAIL_MODULE_H
#define SQUICK_DATA_TRAIL_MODULE_H

#include "squick/base/kernel.h"

#include "squick/base/element.h"
#include "squick/base/class.h"

#include "squick/base/plugin_manager.h"
#include "squick/base/data_tail.h"
#include "squick/base/log.h"

//#include "squick/base/property.h"
//#include "server/game/plugin/logic/if_property_config_module.h"

class NFDataTailModule
    : public IDataTailModule
{
public:
    NFDataTailModule(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual ~NFDataTailModule() {};

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();
    virtual bool AfterInit();

	virtual void LogObjectData(const Guid& self);
    virtual void StartTrail(const Guid& self);

protected:
    void PrintStackTrace();

    int TrailObjectData(const Guid& self);

    int OnClassObjectEvent(const Guid& self, const std::string& className, const CLASS_OBJECT_EVENT classEvent, const DataList& var);

    int OnObjectPropertyEvent(const Guid& self, const std::string& propertyName, const NFData& oldVar, const NFData& newVar, const INT64 reason);

    int OnObjectRecordEvent(const Guid& self, const RECORD_EVENT_DATA& eventData, const NFData& oldVar, const NFData& newVar);

private:

    IKernelModule* m_pKernelModule;
    IElementModule* m_pElementModule;
    IClassModule* m_pClassModule;
    ILogModule* m_pLogModule;
};


#endif
