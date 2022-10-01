

#ifndef SQUICK_CHAT_PLUGIN_H
#define SQUICK_CHAT_PLUGIN_H

///
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

class ChatPlugin : public IPlugin
{
public:
	ChatPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif