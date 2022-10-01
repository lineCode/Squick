

#include "Tutorial5.h"
#include "HelloWorld5.h"

#ifdef NF_DYNAMIC_PLUGIN

NF_EXPORT void DllStartPlugin(IPluginManager* pm)
{

    CREATE_PLUGIN(pm, Tutorial5)

};

NF_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, Tutorial5)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int Tutorial5::GetPluginVersion()
{
    return 0;
}

const std::string Tutorial5::GetPluginName()
{
	return GET_CLASS_NAME(Tutorial5);
}

void Tutorial5::Install()
{
    REGISTER_MODULE(pPluginManager, NFIHelloWorld5, NFHelloWorld5)
    
}

void Tutorial5::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, NFIHelloWorld5, NFHelloWorld5)
}