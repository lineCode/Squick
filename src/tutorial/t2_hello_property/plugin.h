

#ifndef NF_TUTORIAL2_H
#define NF_TUTORIAL2_H

///
#include "NFComm/NFPluginModule/IPlugin.h"
#include "NFComm/NFPluginModule/IPluginManager.h"

class Tutorial2 : public IPlugin
{
public:
    Tutorial2(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif