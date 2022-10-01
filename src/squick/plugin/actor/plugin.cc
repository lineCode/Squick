

#include "plugin.h"
#include "module.h"

#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, ActorPlugin)
};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, ActorPlugin)
};

#endif

//////////////////////////////////////////////////////////////////////////

const int ActorPlugin::GetPluginVersion()
{
    return 0;
}

const std::string ActorPlugin::GetPluginName()
{
	return GET_CLASS_NAME(ActorPlugin);
}

void ActorPlugin::Install()
{
	REGISTER_MODULE(pPluginManager, IActorModule, ActorModule)
}

void ActorPlugin::Uninstall()
{
	UNREGISTER_MODULE(pPluginManager, IActorModule, ActorModule)
}