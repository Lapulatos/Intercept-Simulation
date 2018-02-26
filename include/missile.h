#ifndef MISSILE_INCLUDED
#define MISSILE_INCLUDED

#include "miliobj.h"
#include "bomber.h"
#include "defence.h"

namespace Simu
{

	/////////////////////////////////
	// 导弹的定义
	/////////////////////////////////

	// 前向声明导弹
	class Missile;
        typedef std::shared_ptr<Simu::Missile> MissileHolder;           // 自动释放实例资源
        typedef std::vector<Simu::Missile*> MissileList;                  // 导弹指针表[提高程序运行效率]
        typedef std::vector<Simu::MissileHolder> MissileHolderList;       // 导弹实例表[存储具体实例]

        // 前向声明轰炸机
        class Bomber;
        typedef std::shared_ptr<Simu::Bomber> BomberHolder;     // 自动释放实例资源 
        typedef std::vector<Simu::Bomber*> BomberList;            // 轰炸机指针表[提高程序运行效率]
        typedef std::vector<Simu::BomberHolder> BomberHolderList; // 轰炸机实例表[保存具体实例]

        // 前向声明守方
        class DefenceObject;
        typedef std::shared_ptr<Simu::DefenceObject> DefenceObjectHolder;       // 持有实例，自动释放实例资源
        typedef std::vector<Simu::DefenceObject*> DefenceObjectList;              // 守方实例指针表[提高程序运行效率]
        typedef std::vector<Simu::DefenceObjectHolder> DefenceObjectHolderList;   // 守方实例表[保存具体实例]


	typedef enum MissileStatus
	{
		MISSILE_WAIT_LAUNCH,		// 待发射
		MISSILE_FLIGHTING,		// 飞行途中
		MISSILE_HIT_BOMBER,		// 击中目标
		MISSILE_MISSED,			// 未击中目标
		MISSILE_OUT_ACTION_RADIUS,	// 超出作战范围
		MISSILE_MISSION_COMPLETE	// 任务完成
	} MissileStatus;	// 导弹的状态
	
	class Missile : public MilitaryObject, public MovingObject
	{
	public:
		Missile();
		Missile(const Missile& missile);
		Missile(const unsigned number, const Simu::Position& pos, const Simu::Speed& speed, const catype range, 
			Simu::DefenceObject* subject, Simu::Bomber* bomber, const MissileStatus status);

		void SetObjectExplosionRange(const catype range);
		void SetObjectSubjectTo(Simu::DefenceObject* subject);
		void SetObjectBomber(Simu::Bomber* bomber);
		void SetObjectStatus(const MissileStatus status);
		catype GetObjectExplosionRange() const;
		Simu::DefenceObject* GetObjectSubjectTo() const;
		Simu::Bomber* GetObjectBomber() const;
		MissileStatus GetObjectStatus() const;		

                // 时间更新
                void TimeUpdate();

		// 状态记录
		void StatusRecord();

		// 状态更新
		void ChangeStatusFlighting();
		void ChangeStatusHitBomber();
		void ChangeStatusMissed();
		void ChangeStatusOutActionRadius();
		void ChangeStatusMissionComplete();
	protected:
		catype m_ExplosionRange_;		// 导弹爆破范围
		Simu::DefenceObject* m_SubjectTo_;	// 隶属的守方
		Simu::Bomber* m_Bomber_;		// 导弹拦截的轰炸机
		MissileStatus m_Status_;		// 导弹的状态
	};	// class Missile
	
	// for convenient
	typedef std::shared_ptr<Simu::Missile> MissileHolder;		// 自动释放实例资源
	typedef std::vector<Simu::Missile*> MissileList;			// 导弹指针表[提高程序运行效率]
	typedef std::vector<Simu::MissileHolder> MissileHolderList;	// 导弹实例表[存储具体实例]

}	// namespace Simu


#endif	// MISSILE_INCLUDED
