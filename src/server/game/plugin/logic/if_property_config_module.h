
#ifndef SQUICK_INTF_PROPERTY_CONFIG_MODULE_H
#define SQUICK_INTF_PROPERTY_CONFIG_MODULE_H

#include <iostream>
#include <squick/base/module.h>

class IPropertyConfigModule
    : public IModule
{
public:

    virtual bool LegalLevel(const int nJob, const int nLevel) = 0;
    virtual const std::string& GetInitPropertyID(const int nJob, const int nLevel) = 0;

    virtual void ClearInitPropertyData() = 0;
    virtual void AddInitPropertyID(const int nJob, const int nLevel, const std::string& data) = 0;

    virtual void SetEx(const bool b) = 0;

};


#endif
