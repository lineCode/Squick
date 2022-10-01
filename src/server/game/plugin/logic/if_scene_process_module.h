

#ifndef SQUICK_INTF_SCENEPROCESS_MODULE_H
#define SQUICK_INTF_SCENEPROCESS_MODULE_H

#include <iostream>
#include <squick/base/module.h>

class ISceneProcessModule
    : public IModule
{
public:

	virtual bool RequestEnterScene(const Guid& self, const int sceneID, const int nGrupID, const int type, const Vector3& pos, const DataList& argList) = 0;
};

#endif