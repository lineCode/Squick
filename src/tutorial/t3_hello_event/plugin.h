

#ifndef NF_TUTORIAL3_H
#define NF_TUTORIAL3_H

///
#include "NFComm/NFPluginModule/IPlugin.h"
#include "NFComm/NFPluginModule/IPluginManager.h"

class Tutorial3Plugin : public IPlugin
{
public:
    Tutorial3Plugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif