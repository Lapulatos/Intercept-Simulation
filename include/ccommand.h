#ifndef CCOMMAND_INCLUDED
#define CCOMMAND_INCLUDED

#include "command.h"

#include "offense.h"
#include "defence.h"
#include "missile.h"
#include "bomber.h"
#include "target.h"

namespace Simu
{
    
	/////////////////////////////////
    	// 攻方命令定义
    	/////////////////////////////////
    
    	// 时间更新命令
   	class OffenseTimeUpdateCommand : public Command
    	{
    	public:
        	OffenseTimeUpdateCommand(Simu::OffenseObject* receiver);
        	void* Execute();
    	};    // class OffenseTimeUpdateCommand
    	
   	
    	//----------------------------------------------------------------------------
    	
    	
    	/////////////////////////////////
    	// 守方命令定义
    	/////////////////////////////////
    	
    	// 时间更新命令
    	class DefenceTimeUpdateCommand : public Command
    	{
    	public:
        	DefenceTimeUpdateCommand(Simu::DefenceObject* receiver);
        	void* Execute();
    	};    	// class DefenceTimeUpdateCommand
    	
	
	// 状态更新--待机发弹
	class DefenceObjectStatusChangedToAwaitOrderCommand : public Command
	{
	public:
		DefenceObjectStatusChangedToAwaitOrderCommand(Simu::DefenceObject* receiver);
		void* Execute();
	};	// DefenceObjectStatusChangedToAwaitOrderCommand    	
    	
	// 状态更新--发射导弹
	class DefenceObjectStatusChangedToLaunchMissileCommand : public Command
	{
	public:
		DefenceObjectStatusChangedToLaunchMissileCommand(Simu::DefenceObject* receiver);
		void* Execute();
	};	// DefenceObjectStatusChangedToLaunchMissileCommand
	
    	//----------------------------------------------------------------------------
    	
    	
    	/////////////////////////////////
    	// 导弹命令定义
    	/////////////////////////////////
    	
    	// 时间更新命令
    	class MissileTimeUpdateCommand : public Command
    	{
    	public:
        	MissileTimeUpdateCommand(Simu::Missile* receiver);
        	void* Execute();
    	};	// class MissileTimeUpdateCommand
    	
	// 状态更新--飞行途中
	class MissileStatusChangedToFlightingCommand : public Command
	{
	public:
		MissileStatusChangedToFlightingCommand(Simu::Missile* receiver);
		void* Execute();
	};	// MissileStatusChangedToFlightingCommand
    	
        // 状态更新--击中轰炸机
        class MissileStatusChangedToHitBomberCommand : public Command
        {
        public:
                MissileStatusChangedToHitBomberCommand(Simu::Missile* receiver);
                void* Execute();
        };      // MissileStatusChangedToHitBomberCommand

	// 状态更新--未击中轰炸机
	class MissileStatusChangedToMissedCommand : public Command
	{
	public:
		MissileStatusChangedToMissedCommand(Simu::Missile* receiver);
		void* Execute();
	};	// class MissileStatusChangedToMissedCommand

        // 状态更新--超出作战范围
        class MissileStatusChangedToOutActionRadiusCommand : public Command
        {
        public:
                MissileStatusChangedToOutActionRadiusCommand(Simu::Missile* receiver);
                void* Execute();
        };      // MissileStatusChangedToOutActionRadiusCommand

	// 状态更新--任务完成
	class MissileStatusChangedToMissionCompleteCommand : public Command
	{
	public:
		MissileStatusChangedToMissionCompleteCommand(Simu::Missile* receiver);
		void* Execute();
	};	// class MissileStatusChangedToMissionCompleteCommand

    	//----------------------------------------------------------------------------
    	
    	
    	////////////////////////////////
    	// 轰炸机命令定义
    	////////////////////////////////
    
    	// 时间更新命令
    	class BomberTimeUpdateCommand : public Command
    	{
    	public:
        	BomberTimeUpdateCommand(Simu::Bomber* receiver);
        	void* Execute();
    	};    	//class BomberTimeUpdateCommand
    	
	// 状态改变--前往守方军事目标命令
	class BomberStatusChangedToLeaveForTargetCommand : public Command
	{
	public: 
		BomberStatusChangedToLeaveForTargetCommand(Simu::Bomber* receiver);
		void* Execute();
	};	// class BomberStatusChangedToLeaveForTargetCommand    	

	// 状态改变--击毁命令
	class BomberStatusChangedToCrashedCommand : public Command
	{
	public:
		BomberStatusChangedToCrashedCommand(Simu::Bomber* receiver);
		void* Execute();
	};	// class BomberStatusChangedToCrashedCommand

        // 状态改变--返回基地命令
        class BomberStatusChangedToReturnBaseCommand : public Command
        {
        public:
                BomberStatusChangedToReturnBaseCommand(Simu::Bomber* receiver);
                void* Execute();
        };      // class BomberStatusChangedToReturnBaseCommand

        // 状态改变--完成任务命令
        class BomberStatusChangedToMissionCompleteCommand : public Command
        {
        public:
                BomberStatusChangedToMissionCompleteCommand(Simu::Bomber* receiver);
                void* Execute();
        };      // class BomberStatusChangedToMissionCompleteCommand


    	//----------------------------------------------------------------------------
    	
    	
    	////////////////////////////////
    	// 守方军事目标命令定义
    	////////////////////////////////
    	
    	// 时间更新命令定义
    	class TargetTimeUpdateCommand : public Command
    	{
    	public:
        	TargetTimeUpdateCommand(Simu::Target* receiver);
        	void* Execute();
    	};    	// class TargetTimeUpdateCommand

	// 改变状态--遭到破坏命令
	class TargetStatusChangedToDestroyedCommand : public Command
	{
	public:
		TargetStatusChangedToDestroyedCommand(Simu::Target* receiver);
		void* Execute();
	};	// class TargetStatusChangedToDestroyedCommand
    	
    	//----------------------------------------------------------------------------
    	//----------------------------------------------------------------------------
    	//----------------------------------------------------------------------------
    	//----------------------------------------------------------------------------
    	//----------------------------------------------------------------------------
    	//----------------------------------------------------------------------------
    	//----------------------------------------------------------------------------
    	//----------------------------------------------------------------------------
    	//----------------------------------------------------------------------------
    	//----------------------------------------------------------------------------
    	//----------------------------------------------------------------------------
    	//----------------------------------------------------------------------------
    	//----------------------------------------------------------------------------
    
}    // namespace Simu

#endif  // CCOMMAND_INCLUDED
