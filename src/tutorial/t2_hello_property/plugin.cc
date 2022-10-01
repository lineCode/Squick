
#include "Tutorial2.h"
#include "HelloWorld2.h"

#ifdef NF_DYNAMIC_PLUGIN

NF_EXPORT void DllStartPlugin(IPluginManager* pm)
{

    CREATE_PLUGIN(pm, Tutorial2)

};

NF_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, Tutorial2)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int Tutorial2::GetPluginVersion()
{
    return 0;
}

const std::string Tutorial2::GetPluginName()
{
	return GET_CLASS_NAME(Tutorial2);
}

void Tutorial2::Install()
{
    REGISTER_MODULE(pPluginManager, IHelloProperty, HelloProperty)
    
}

void Tutorial2::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, IHelloProperty, HelloProperty)
}