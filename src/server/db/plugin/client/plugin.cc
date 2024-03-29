

#include "plugin.h"
#include "world_module.h"

//
//
#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{

    CREATE_PLUGIN(pm, Net_ClientPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, Net_ClientPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int Net_ClientPlugin::GetPluginVersion()
{
    return 0;
}

const std::string Net_ClientPlugin::GetPluginName()
{
	return GET_CLASS_NAME(Net_ClientPlugin);
}

void Net_ClientPlugin::Install()
{
    REGISTER_MODULE(pPluginManager, IDBToWorldModule, DBToWorldModule)
}

void Net_ClientPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, IDBToWorldModule, DBToWorldModule)
}