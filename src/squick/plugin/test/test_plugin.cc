#include "test_module.h"
#include "test_plugin.h"

#ifdef NF_DYNAMIC_PLUGIN

NF_EXPORT void DllStartPlugin(IPluginManager* pm)
{

    CREATE_PLUGIN(pm, TestPlugin)

};

NF_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, TestPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int TestPlugin::GetPluginVersion()
{
    return 0;
}

const std::string TestPlugin::GetPluginName()
{
	return GET_CLASS_NAME(TestPlugin);
}

void TestPlugin::Install()
{
    std::cout << "TestPlugin::Install" << std::endl;
    REGISTER_MODULE(pPluginManager, NFITestModule, TestModule)

}

void TestPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, NFITestModule, TestModule)
}