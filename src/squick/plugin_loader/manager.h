
#ifndef SQUICK_PLUGIN_MANAGER_H
#define SQUICK_PLUGIN_MANAGER_H

#include <map>
#include <string>
#include <time.h>
#include <thread>
#include "dyn_lib.h"
#include "squick/base/module.h"
#include "squick/base/plugin_manager.h"

class PluginManager
    : public IPluginManager
{
public:
    PluginManager();
    virtual ~PluginManager();

    virtual bool LoadPluginConfig() override;

    virtual bool LoadPlugin() override;

    virtual bool Awake() override;

    virtual bool Init() override;

    virtual bool AfterInit() override;

    virtual bool CheckConfig() override;

    virtual bool ReadyExecute() override;

    virtual bool BeforeShut() override;

    virtual bool Shut() override;

    virtual bool Finalize() override;


    //////////////////////////////////////////////////////////////////////////

    virtual void Registered(IPlugin* pPlugin) override;

    virtual void UnRegistered(IPlugin* pPlugin) override;

    //////////////////////////////////////////////////////////////////////////

    virtual bool ReLoadPlugin(const std::string& pluginDLLName) override;

    virtual IPlugin* FindPlugin(const std::string& pluginName) override;

    virtual void AddModule(const std::string& moduleName, IModule* pModule) override;

    virtual void AddTestModule(const std::string& moduleName, IModule* pModule) override;

    virtual void RemoveModule(const std::string& moduleName) override;

    virtual IModule* FindModule(const std::string& moduleName) override;

    virtual IModule* FindTestModule(const std::string& moduleName) override;

	virtual std::list<IModule*> Modules() override;
	virtual std::list<IModule*> TestModules() override;

    virtual bool Execute() override;

    virtual int GetAppID() const override;
    virtual void SetAppID(const int appID) override;

	virtual int GetAppType() const override;
	virtual void SetAppType(const int type) override;

    virtual bool IsRunningDocker() const override;
    virtual void SetRunningDocker(bool bDocker) override;

    virtual bool IsStaticPlugin() const override;

    virtual INT64 GetInitTime() const override;
    virtual INT64 GetNowTime() const override;

    virtual const std::string& GetConfigPath() const override;
    virtual void SetConfigPath(const std::string & strPath) override;

    virtual void SetConfigName(const std::string& fileName) override;
    virtual const std::string& GetConfigName() const override;

    virtual const std::string& GetAppName() const override;

    virtual void SetAppName(const std::string& appName) override;

    virtual const std::string& GetLogConfigName() const override;

    virtual void SetLogConfigName(const std::string& name) override;

    virtual IPlugin* GetCurrentPlugin() override;
    virtual IModule* GetCurrentModule() override;

    virtual void SetCurrentPlugin(IPlugin* pPlugin) override;
    virtual void SetCurrentModule(IModule* pModule) override;

	virtual int GetAppCPUCount() const override;
	virtual void SetAppCPUCount(const int count) override;

	virtual bool UsingBackThread() const override;
	virtual void SetUsingBackThread(const bool b) override;

    virtual void SetGetFileContentFunctor(GET_FILECONTENT_FUNCTOR fun) override;

    virtual bool GetFileContent(const std::string &fileName, std::string &content) override;

	virtual void AddFileReplaceContent(const std::string& fileName, const std::string& content, const std::string& newValue) override;
	virtual std::vector<ReplaceContent> GetFileReplaceContents(const std::string& fileName) override;

protected:

    bool CheckStaticPlugin();

    bool LoadStaticPlugin(const std::string& pluginDLLName);
    bool LoadPluginLibrary(const std::string& pluginDLLName);
    bool UnLoadPluginLibrary(const std::string& pluginDLLName);
    bool UnLoadStaticPlugin(const std::string& pluginDLLName);

private:
    int appID = 0;
	int appType = 0;
    bool mbIsDocker = false;
	bool mbStaticPlugin = false;
	bool usingBackThread = false;

    INT64 mnInitTime = 0;
	INT64 mnNowTime = 0;
	INT64 mnCPUCount = 8;

    std::string configPath;
    std::string configName;
    std::string appName;
    std::string logConfigName;

    IPlugin* currentPlugin;
    IModule* currentModule;

    typedef std::map<std::string, bool> PluginNameMap;
    typedef std::map<std::string, DynLib*> PluginLibMap;
    typedef std::map<std::string, IPlugin*> PluginInstanceMap;
    typedef std::map<std::string, IModule*> ModuleInstanceMap;
    typedef std::map<std::string, IModule*> TestModuleInstanceMap;
    typedef std::vector<std::pair<std::string, IModule*>> NeedExecuteModuleVec;

    typedef void(* DLL_START_PLUGIN_FUNC)(IPluginManager* pm);
    typedef void(* DLL_STOP_PLUGIN_FUNC)(IPluginManager* pm);

    std::vector<std::string> mStaticPlugin;
	std::map<std::string, std::vector<ReplaceContent>> mReplaceContent;

    PluginNameMap mPluginNameMap;
    PluginLibMap mPluginLibMap;
    PluginInstanceMap mPluginInstanceMap;
    ModuleInstanceMap mModuleInstanceMap;
    TestModuleInstanceMap mTestModuleInstanceMap;
    NeedExecuteModuleVec mNeedExecuteModuleVec;

    GET_FILECONTENT_FUNCTOR mGetFileContentFunctor;
};

#endif
