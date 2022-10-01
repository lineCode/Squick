


#ifndef SQUICK_INTF_CREATE_ROLE_MODULE_H
#define SQUICK_INTF_CREATE_ROLE_MODULE_H

#include <iostream>
#include <squick/base/module.h>

class ICreateRoleModule : public IModule
{
public:
	virtual void SetDefaultSceneID(const int sceneID) = 0;
};

#endif