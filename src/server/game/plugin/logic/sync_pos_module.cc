


#include "sync_pos_module.h"
#include "squick/base/net.h"
#include "squick/struct/msg_share.pb.h"
#include "squick/struct/protocol_define.h"
#include "squick/plugin/kernel/scene_module.h"

bool SyncPosModule::Init()
{

	m_pScheduleModule = pPluginManager->FindModule<NFIScheduleModule>();
	m_pNetModule = pPluginManager->FindModule<INetModule>();
	m_pKernelModule = pPluginManager->FindModule<IKernelModule>();
	m_pElementModule = pPluginManager->FindModule<IElementModule>();
	m_pGameServerNet_ServerModule = pPluginManager->FindModule<IGameServerNet_ServerModule>();
	m_pSceneModule = pPluginManager->FindModule<ISceneModule>();
	m_pClassModule = pPluginManager->FindModule<IClassModule>();
	m_pLogModule = pPluginManager->FindModule<ILogModule>();
	
    return true;
}

bool SyncPosModule::Shut()
{
    return true;
}

bool SyncPosModule::Execute()
{
	//should be processed by actor's component
	//15 times per second
	static int64_t timePassed = NFGetTimeMS();
	int64_t nowTime = NFGetTimeMS();
	if (nowTime - timePassed >= 50)
	{
		timePassed = nowTime;

		auto sceneInfo = m_pSceneModule->First();
		while (sceneInfo)
		{
			auto groupInfo = sceneInfo->First();
			while (groupInfo)
			{
				if (groupInfo->mPlayerPosition.size() > 0)
				{
					SquickStruct::ReqAckPlayerPosSync playerPosSync;
					for (auto var : groupInfo->mPlayerPosition)
					{
						SquickStruct::PosSyncUnit* posSyncUnit = playerPosSync.add_sync_unit();
						if (posSyncUnit)
						{
							*posSyncUnit->mutable_mover() = INetModule::StructToProtobuf(var.second.mover);
							*posSyncUnit->mutable_pos() = INetModule::StructToProtobuf(var.second.pos);
							*posSyncUnit->mutable_orientation() = INetModule::StructToProtobuf(var.second.orientation);
							posSyncUnit->set_status(var.second.status);
							posSyncUnit->set_type((SquickStruct::PosSyncUnit_EMoveType)var.second.type);
						}
					}

					groupInfo->mPlayerPosition.clear();
					playerPosSync.set_sequence(groupInfo->sequence++);

					m_pGameServerNet_ServerModule->SendGroupMsgPBToGate(SquickStruct::ACK_MOVE, playerPosSync, sceneInfo->sceneID, groupInfo->groupID);
				}

				groupInfo = sceneInfo->Next();
			}

			sceneInfo = m_pSceneModule->Next();
		}
	}

    return true;
}

bool SyncPosModule::AfterInit()
{

	m_pKernelModule->AddClassCallBack(SquickProtocol::NPC::ThisName(), this, &SyncPosModule::OnNPCClassEvent);
	m_pKernelModule->AddClassCallBack(SquickProtocol::Player::ThisName(), this, &SyncPosModule::OnPlayerClassEvent);

    return true;
}

bool SyncPosModule::RequireMove(const Guid scene_group, const PosSyncUnit& syncUnit)
{
	std::shared_ptr<SceneInfo> sceneInfo = m_pSceneModule->GetElement(scene_group.GetHead());
	if (sceneInfo)
	{
		std::shared_ptr<SceneGroupInfo> groupInfo = sceneInfo->GetElement(scene_group.GetData());
		if (groupInfo)
		{
			groupInfo->mPlayerPosition[syncUnit.mover] = syncUnit;
		}
	}

	return true;
}

int SyncPosModule::OnNPCClassEvent(const Guid & self, const std::string & className, const CLASS_OBJECT_EVENT classEvent, const DataList & var)
{
	if (CLASS_OBJECT_EVENT::COE_CREATE_FINISH == classEvent)
	{
	}

	return 0;
}

int SyncPosModule::OnNPCGMPositionEvent(const Guid & self, const std::string & propertyName, const NFData & oldVar, const NFData & newVar)
{
	return 0;
}

int SyncPosModule::OnPlayerClassEvent(const Guid & self, const std::string & className, const CLASS_OBJECT_EVENT classEvent, const DataList & var)
{
	if (CLASS_OBJECT_EVENT::COE_CREATE_FINISH == classEvent)
	{
		m_pKernelModule->AddPropertyCallBack(self, SquickProtocol::Player::MoveTo(), this, &SyncPosModule::OnPlayerGMPositionEvent);
		m_pKernelModule->AddPropertyCallBack(self, SquickProtocol::Player::GMMoveTo(), this, &SyncPosModule::OnPlayerGMPositionEvent);
	}

	return 0;
}

int SyncPosModule::OnPlayerGMPositionEvent(const Guid & self, const std::string & propertyName, const NFData & oldVar, const NFData & newVar, const INT64 reason)
{
	SquickStruct::ReqAckPlayerPosSync xMsg;
	SquickStruct::PosSyncUnit* syncUnit = xMsg.add_sync_unit();
	if (syncUnit)
	{
		const Vector3& v = newVar.GetVector3();
		*syncUnit->mutable_pos() = INetModule::StructToProtobuf(v);
		*syncUnit->mutable_mover() = INetModule::StructToProtobuf(self);
		syncUnit->set_type(SquickStruct::PosSyncUnit_EMoveType::PosSyncUnit_EMoveType_EET_TELEPORT);

		m_pKernelModule->SetPropertyVector3(self, SquickProtocol::IObject::Position(), v);

		const int sceneID = m_pKernelModule->GetPropertyInt32(self, SquickProtocol::Player::SceneID());
		const int groupID = m_pKernelModule->GetPropertyInt32(self, SquickProtocol::Player::GroupID());

		m_pGameServerNet_ServerModule->SendGroupMsgPBToGate(SquickStruct::ACK_MOVE, xMsg, sceneID, groupID);
	}

	return 0;
}
