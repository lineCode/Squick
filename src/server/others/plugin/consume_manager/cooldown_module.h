

#ifndef SQUICK_COOLDOW_MODULE_H
#define SQUICK_COOLDOW_MODULE_H


#include <squick/base/kernel.h>
#include <squick/base/element.h>
#include "if_cooldown_module.h"


class CooldownModule
        : public ICooldownModule
{
public:

    CooldownModule(IPluginManager* p )
    {
        pPluginManager = p;
    }

    virtual bool AfterInit() override;

    virtual void AddCooldown(const Guid& self, const std::string& configID );
    virtual bool ExistCooldown(const Guid& self, const std::string& configID );

private:

    IKernelModule* m_pKernelModule;
    IElementModule* m_pElementModule;
};

#endif
