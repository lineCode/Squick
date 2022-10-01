

#ifndef SQUICK_INTF_SYNC_POS_MODULE_H
#define SQUICK_INTF_SYNC_POS_MODULE_H

#include <iostream>
#include <squick/base/module.h>

class PosSyncUnit;

class ISyncPosModule
    : public IModule
{
public:
    virtual bool RequireMove(const Guid scene_group, const PosSyncUnit& syncUnit) = 0;
};

#endif