

#include "plugin.h"
#include "game_server_module.h"


bool GameServerModule::Init()
{
    m_pKernelModule = pPluginManager->FindModule<IKernelModule>();
    m_pClassModule = pPluginManager->FindModule<IClassModule>();
    return true;
}

bool GameServerModule::Shut()
{

    return true;
}

bool GameServerModule::Execute()
{
#ifdef _DEBUG
    /*
    char szContent[MAX_PATH] = { 0 };
    if (kbhit() && gets(szContent))
    {
        DataList val(szContent, ",");
        if (val.GetCount() > 0)
        {
            //const char* pstrCmd = val.String( 0 );
            m_pKernelModule->Command(val);

        }
    }
    */
#endif


    return true;
}

bool GameServerModule::AfterInit()
{


    return true;
}

bool GameServerModule::BeforeShut()
{

    return true;
}