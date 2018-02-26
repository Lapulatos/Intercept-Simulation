#ifndef BOMBER_INCLUDED
#define BOMBER_INCLUDED

#include "miliobj.h"
#include "target.h"

namespace Simu
{

	/////////////////////////////////////
	// 轰炸机的定义
	/////////////////////////////////////

	// 前向声明轰炸机
	class Bomber;
        typedef std::shared_ptr<Simu::Bomber> BomberHolder;     // 自动释放实例资源
        typedef std::vector<Simu::Bomber*> BomberList;            // 轰炸机指针表[提高程序运行效率]
        typedef std::vector<Simu::BomberHolder> BomberHolderList; // 轰炸机实例表[保存具体实例]

        // 前向声明军事目标
        class Target;
        typedef std::shared_ptr<Simu::Target> TargetHolder;     // 自动释放实例资源
        typedef std::vector<Simu::Target*> TargetList;            // 守方指针列表[提高程序运行效率]
        typedef std::vector<Simu::TargetHolder> TargetHolderList; // 守方实例列表

        // 前向声明攻方
        class OffenseObject;
        typedef std::shared_ptr<Simu::OffenseObject> OffenseObjectHolder;       // 自动释放实例资源
        typedef std::vector<Simu::OffenseObject*> OffenseObjectList;            // 攻方指针列表[提高运行效率]
        typedef std::vector<Simu::OffenseObjectHolder> OffenseObjectHolderList; // 攻方实例列表


	typedef enum BomberStatus
	{
		BOMBER_WAIT_LAUNCH,		// 待发射
		BOMBER_LEAVE_FOR_TARGET,	// 前往守方军事目标
		BOMBER_CRASHED,			// 击毁
		BOMBER_RETURN_BASE,		// 返回基地
		BOMBER_MISSION_COMPLETE		// 完成任务
	} BomberStatus;	// 轰炸机的状态

	// the definitaion of bomber
	class Bomber : public MilitaryObject, public MovingObject
	{
	public:
		Bomber();
		Bomber(const Bomber& bomber);
		Bomber(const unsigned number, const unsigned launch, 
		       const Simu::Position& pos, const Simu::Speed& speed, 
		       Simu::Target* target, Simu::OffenseObject* subject, const BomberStatus status);

		void SetObjectLaunchTime(const unsigned launch);
		void SetObjectTarget(Simu::Target* target);
		void SetObjectSubjectTo(Simu::OffenseObject* subject);
		void SetObjectStatus(const BomberStatus status);
		unsigned GetObjectLaunchTime() const;
		Simu::Target* GetObjectTarget() const;
		Simu::OffenseObject* GetObjectSubjectTo();
		BomberStatus GetObjectStatus() const;

                // 时间更新
                void TimeUpdate();

		// 状态记录
		void StatusRecord();

		// 状态更新
		void ChangeStatusLeaveForTarget();
		void ChangeStatusCrashed();
		void ChangeStatusReturnBase();
		void ChangeStatusMissionComplete();
	protected:
		unsigned m_LaunchTime_;			// 起飞时间
		Simu::Target* m_Target_;		// 轰炸的军事目标
		Simu::OffenseObject* m_SubjectTo_;	// 隶属的攻方
		BomberStatus m_Status_;			// 轰炸机的状态
	};	// class Bomber
	
}	// namespace Simu


#endif	// BOMBER_INCLUDED

