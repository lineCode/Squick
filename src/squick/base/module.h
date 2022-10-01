

#ifndef SQUICK_INTF_MODULE_H
#define SQUICK_INTF_MODULE_H

#include <string>
#include "plugin_manager.h"
#include "squick/core/map.h"
#include "squick/core/list.h"
#include "squick/core/data_list.h"
#include "squick/core/smart_enum.h"

class IModule
{

public:
    IModule() : m_bIsExecute(false), pPluginManager(NULL)
    {
    }

    virtual ~IModule() {}

    virtual bool Awake()
    {
        return true;
    }

    virtual bool Init()
    {

        return true;
    }

    virtual bool AfterInit()
    {
        return true;
    }

    virtual bool CheckConfig()
    {
        return true;
    }

    virtual bool ReadyExecute()
    {
        return true;
    }

    virtual bool Execute()
    {
        return true;
    }

    virtual bool BeforeShut()
    {
        return true;
    }

    virtual bool Shut()
    {
        return true;
    }

    virtual bool Finalize()
    {
        return true;
    }

	virtual bool OnReloadPlugin()
	{
		return true;
	}

    virtual IPluginManager* GetPluginManager() const
    {
        return pPluginManager;
    }

    std::string name;
    bool m_bIsExecute;
protected:
	IPluginManager* pPluginManager;
};
#endif
