

#include "item_consume_manager_module.h"

bool ItemConsumeManagerModule::Init()
{

    return true;
}

bool ItemConsumeManagerModule::Shut()
{

    return true;
}

bool ItemConsumeManagerModule::Execute()
{

    return true;
}

bool ItemConsumeManagerModule::AfterInit()
{

    return true;
}

bool ItemConsumeManagerModule::SetConsumeModule(const int itemType, const int itemSubType, IItemConsumeProcessModule* pModule)
{
	mItemConsumeModule[Guid(itemType, itemSubType)] = pModule;

	return true;
}

IItemConsumeProcessModule* ItemConsumeManagerModule::GetConsumeModule(const int itemType, const int itemSubType)
{
	auto it = mItemConsumeModule.find(Guid(itemType, itemSubType));
	if (it != mItemConsumeModule.end())
	{
		return it->second;
	}
	else
	{
		it = mItemConsumeModule.find(Guid(itemType, 0));
		if (it != mItemConsumeModule.end())
		{
			return it->second;
		}
	}

	return nullptr;
}

bool ItemConsumeManagerModule::SetConsumeModule(const int itemType, IItemConsumeProcessModule* pModule)
{
	mItemConsumeModule[Guid(itemType, 0)] = pModule;

	return true;
}

IItemConsumeProcessModule* ItemConsumeManagerModule::GetConsumeModule(const int itemType)
{
	auto it = mItemConsumeModule.find(Guid(itemType, 0));
	if (it != mItemConsumeModule.end())
	{
		return it->second;
	}

	return nullptr;
}