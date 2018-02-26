#include "ccommand.h"

namespace Simu
{
    
	/////////////////////////////////
    	// 攻方命令实现
    	/////////////////////////////////
    
    	// 时间更新命令实现
    	OffenseTimeUpdateCommand::OffenseTimeUpdateCommand(Simu::OffenseObject* receiver) :
        	Simu::Command(receiver, CMD_RECVR_OFFENSE)
    	{}
    
    	void* OffenseTimeUpdateCommand::Execute()
    	{
        	(static_cast<Simu::OffenseObject*>(m_Receiver_))->TimeUpdate();    // 执行时间更新命令
        	return nullptr;
    	}
    
    
    	//------------------------------------------------------------------------
    
    	/////////////////////////////////
    	// 守方命令实现
    	/////////////////////////////////
    
    	// 时间更新命令实现
    	DefenceTimeUpdateCommand::DefenceTimeUpdateCommand(Simu::DefenceObject* receiver) :
        	Simu::Command(receiver, CMD_RECVR_DEFENCE)
    	{}
    
   	void* DefenceTimeUpdateCommand::Execute()
    	{
        	(static_cast<Simu::DefenceObject*>(m_Receiver_))->TimeUpdate();    // 执行时间更新命令
        	return nullptr;
    	}
    
        // 状态更新--待机发弹  
	DefenceObjectStatusChangedToAwaitOrderCommand::DefenceObjectStatusChangedToAwaitOrderCommand(Simu::DefenceObject* receiver) :
		Simu::Command(receiver, CMD_RECVR_DEFENCE)
	{}

        void* DefenceObjectStatusChangedToAwaitOrderCommand::Execute()
	{
		(static_cast<Simu::DefenceObject*>(m_Receiver_))->ChangeStatusAwaitOrder();
		return nullptr;
	}

        // 状态更新--发射导弹
	DefenceObjectStatusChangedToLaunchMissileCommand::DefenceObjectStatusChangedToLaunchMissileCommand(Simu::DefenceObject* receiver) :
		Simu::Command(receiver, CMD_RECVR_DEFENCE)
	{}

	void* DefenceObjectStatusChangedToLaunchMissileCommand::Execute()
	{
		(static_cast<Simu::DefenceObject*>(m_Receiver_))->ChangeStatusLaunchMissile();
		return nullptr;
	}

    
    	//------------------------------------------------------------------------
    
    	/////////////////////////////////
    	// 导弹命令实现
    	/////////////////////////////////
    
    	// 时间更新命令实现
    	MissileTimeUpdateCommand::MissileTimeUpdateCommand(Simu::Missile* receiver) :
        	Simu::Command(receiver, CMD_RECVR_MISSILE)
    	{}
    
    	void* MissileTimeUpdateCommand::Execute()
    	{
        	(static_cast<Simu::Missile*>(m_Receiver_))->TimeUpdate();    // 执行时间更新命令
        	return nullptr;
    	}
    
        // 状态更新--飞行途中
	MissileStatusChangedToFlightingCommand::MissileStatusChangedToFlightingCommand(Simu::Missile* receiver) :
		Simu::Command(receiver, CMD_RECVR_MISSILE)
	{}
	
	void* MissileStatusChangedToFlightingCommand::Execute()
	{
		(static_cast<Simu::Missile*>(m_Receiver_))->ChangeStatusFlighting();
		return nullptr;
	}

        // 状态更新--击中轰炸机
	MissileStatusChangedToHitBomberCommand::MissileStatusChangedToHitBomberCommand(Simu::Missile* receiver) :
		Simu::Command(receiver, CMD_RECVR_MISSILE)
	{}

	void* MissileStatusChangedToHitBomberCommand::Execute()
	{
		(static_cast<Simu::Missile*>(m_Receiver_))->ChangeStatusHitBomber();
		return nullptr;
	}
	
	// 状态更新--未击中轰炸机
	MissileStatusChangedToMissedCommand::MissileStatusChangedToMissedCommand(Simu::Missile* receiver) :
		Simu::Command(receiver, CMD_RECVR_MISSILE)
	{}

	void* MissileStatusChangedToMissedCommand::Execute()
	{
		(static_cast<Simu::Missile*>(m_Receiver_))->ChangeStatusMissed();
		return nullptr;
	}

        // 状态更新--超出作战范围
	MissileStatusChangedToOutActionRadiusCommand::MissileStatusChangedToOutActionRadiusCommand(Simu::Missile* receiver) :
		Simu::Command(receiver, CMD_RECVR_MISSILE)
	{}

	void* MissileStatusChangedToOutActionRadiusCommand::Execute()
	{
		(static_cast<Simu::Missile*>(m_Receiver_))->ChangeStatusOutActionRadius();
		return nullptr;
	}  

	// 状态更新--任务完成
	MissileStatusChangedToMissionCompleteCommand::MissileStatusChangedToMissionCompleteCommand(Simu::Missile* receiver) :
		Simu::Command(receiver, CMD_RECVR_MISSILE)
	{}
	
	void* MissileStatusChangedToMissionCompleteCommand::Execute()
	{
		(static_cast<Simu::Missile*>(m_Receiver_))->ChangeStatusMissionComplete();
		return nullptr;
	}

    	//------------------------------------------------------------------------
    
    	/////////////////////////////////
    	// 轰炸机机群命令实现
    	/////////////////////////////////
    
    	// 时间更新命令实现
    	BomberTimeUpdateCommand::BomberTimeUpdateCommand(Simu::Bomber* receiver) :
        	Simu::Command(receiver, CMD_RECVR_BOMBER)
    	{}
    
    	void* BomberTimeUpdateCommand::Execute()
    	{
        	(static_cast<Simu::Bomber*>(m_Receiver_))->TimeUpdate();
        	return nullptr;
    	}

        // 状态改变--前往守方军事目标命令
        BomberStatusChangedToLeaveForTargetCommand::BomberStatusChangedToLeaveForTargetCommand(Simu::Bomber* receiver) :
		Simu::Command(receiver, CMD_RECVR_BOMBER)
	{}

        void* BomberStatusChangedToLeaveForTargetCommand::Execute()
	{
		(static_cast<Simu::Bomber*>(m_Receiver_))->ChangeStatusLeaveForTarget();
		return nullptr;
	}

        // 状态改变--击毁命令
        BomberStatusChangedToCrashedCommand::BomberStatusChangedToCrashedCommand(Simu::Bomber* receiver) :
		Simu::Command(receiver, CMD_RECVR_BOMBER)
	{}

        void* BomberStatusChangedToCrashedCommand::Execute()
	{
		(static_cast<Simu::Bomber*>(m_Receiver_))->ChangeStatusCrashed();
		return nullptr;
	}

        // 状态改变--返回基地命令
        BomberStatusChangedToReturnBaseCommand::BomberStatusChangedToReturnBaseCommand(Simu::Bomber* receiver) :
		Simu::Command(receiver, CMD_RECVR_BOMBER)
	{}

        void* BomberStatusChangedToReturnBaseCommand::Execute()
	{
		(static_cast<Simu::Bomber*>(m_Receiver_))->ChangeStatusReturnBase();
		return nullptr;
	}

        // 状态改变--完成任务命令
        BomberStatusChangedToMissionCompleteCommand::BomberStatusChangedToMissionCompleteCommand(Simu::Bomber* receiver) :
		Simu::Command(receiver, CMD_RECVR_BOMBER)
	{}

        void* BomberStatusChangedToMissionCompleteCommand::Execute()
	{
		(static_cast<Simu::Bomber*>(m_Receiver_))->ChangeStatusMissionComplete();
		return nullptr;
	}
    
    
    	//------------------------------------------------------------------------
    
    	/////////////////////////////////
    	// 守方军事目标命令实现
    	/////////////////////////////////
    
    	// 时间更新命令实现
    	TargetTimeUpdateCommand::TargetTimeUpdateCommand(Simu::Target* receiver) :
        	Simu::Command(receiver, CMD_RECVR_TARGET)
    	{}
    
    	void* TargetTimeUpdateCommand::Execute()
    	{
        	(static_cast<Simu::Target*>(m_Receiver_))->TimeUpdate();
        	return nullptr;
    	}
   
	// 改变状态--遭到破坏命令
	TargetStatusChangedToDestroyedCommand::TargetStatusChangedToDestroyedCommand(Simu::Target* receiver) :
		Simu::Command(receiver, CMD_RECVR_TARGET)
	{}

	void* TargetStatusChangedToDestroyedCommand::Execute()
	{
		(static_cast<Simu::Target*>(m_Receiver_))->ChangeStatusDestroyed();
		return nullptr;
	}
 
    	//------------------------------------------------------------------------
    	//------------------------------------------------------------------------
    	/////////////////////////////////
    	/////////////////////////////////
    	//------------------------------------------------------------------------
    	/////////////////////////////////
    	/////////////////////////////////
    	//------------------------------------------------------------------------
    	/////////////////////////////////
    	/////////////////////////////////
    	/////////////////////////////////
    	/////////////////////////////////
    	//------------------------------------------------------------------------
    	/////////////////////////////////
    	/////////////////////////////////
    	//------------------------------------------------------------------------
    	/////////////////////////////////
    	/////////////////////////////////
    	//------------------------------------------------------------------------
    	/////////////////////////////////
    	/////////////////////////////////
    	//------------------------------------------------------------------------
    	/////////////////////////////////
    	/////////////////////////////////
    	//------------------------------------------------------------------------
    	/////////////////////////////////
    	/////////////////////////////////
    	//------------------------------------------------------------------------
    	/////////////////////////////////
    	/////////////////////////////////
    	//------------------------------------------------------------------------
    	//------------------------------------------------------------------------
    	//------------------------------------------------------------------------
    
}    // namespace Simu

