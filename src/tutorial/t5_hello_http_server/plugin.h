
#ifndef NF_TUTORIAL5_H
#define NF_TUTORIAL5_H

///
#include "NFComm/NFPluginModule/IPlugin.h"
#include "NFComm/NFPluginModule/IPluginManager.h"

class Tutorial5 : public IPlugin
{
public:
	Tutorial5(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif