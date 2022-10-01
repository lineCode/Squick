
#include "Tutorial3Plugin.h"
#include "HelloEventModule.h"

#ifdef NF_DYNAMIC_PLUGIN

NF_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, Tutorial3Plugin)
};

NF_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, Tutorial3Plugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int Tutorial3Plugin::GetPluginVersion()
{
    return 0;
}

const std::string Tutorial3Plugin::GetPluginName()
{
	return GET_CLASS_NAME(Tutorial3Plugin);
}

void Tutorial3Plugin::Install()
{

    REGISTER_MODULE(pPluginManager, IHelloEventModule, HelloEventModule)

}

void Tutorial3Plugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, IHelloEventModule, HelloEventModule)
}
