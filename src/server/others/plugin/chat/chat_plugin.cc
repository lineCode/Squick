

#include "chat_module.h"
#include "chat_plugin.h"

//
//
#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{

    CREATE_PLUGIN(pm, ChatPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, ChatPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int ChatPlugin::GetPluginVersion()
{
    return 0;
}

const std::string ChatPlugin::GetPluginName()
{
	return GET_CLASS_NAME(ChatPlugin);
}

void ChatPlugin::Install()
{
    REGISTER_MODULE(pPluginManager, IChatModule, ChatModule)

}

void ChatPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, IChatModule, ChatModule)
}