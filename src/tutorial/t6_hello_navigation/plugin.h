
#ifndef NF_TUTORIAL6_H
#define NF_TUTORIAL6_H

///
#include "NFComm/NFPluginModule/IPlugin.h"
#include "NFComm/NFPluginModule/IPluginManager.h"

class Tutorial6 : public IPlugin
{
public:
	Tutorial6(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif