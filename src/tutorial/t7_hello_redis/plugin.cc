

#include "Tutorial7.h"
#include "HelloWorld7.h"

#ifdef NF_DYNAMIC_PLUGIN

NF_EXPORT void DllStartPlugin(IPluginManager* pm)
{

    CREATE_PLUGIN(pm, Tutorial7)

};

NF_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, Tutorial7)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int Tutorial7::GetPluginVersion()
{
    return 0;
}

const std::string Tutorial7::GetPluginName()
{
	return GET_CLASS_NAME(Tutorial7);
}

void Tutorial7::Install()
{
    REGISTER_MODULE(pPluginManager, NFIHelloWorld7, NFHelloWorld7)
    
}

void Tutorial7::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, NFIHelloWorld7, NFHelloWorld7)
}