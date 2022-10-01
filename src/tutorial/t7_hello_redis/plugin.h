
#ifndef NF_TUTORIAL7_H
#define NF_TUTORIAL7_H

///
#include "NFComm/NFPluginModule/IPlugin.h"
#include "NFComm/NFPluginModule/IPluginManager.h"

class Tutorial7 : public IPlugin
{
public:
	Tutorial7(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif