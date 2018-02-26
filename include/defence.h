#ifndef DEFENCE_INCLUDED
#define DEFENCE_INCLUDED

#include "miliobj.h"
#include "target.h"
#include "bomber.h"
#include "missile.h"

namespace Simu
{

	////////////////////////////////////
	// 防守方的定义
	////////////////////////////////////

	// 前向声明导弹类
        class Missile;
        typedef std::shared_ptr<Simu::Missile> MissileHolder;           // 自动释放实例资源
        typedef std::vector<Simu::Missile*> MissileList;                  // 导弹指针表[提高程序运行效率]
        typedef std::vector<Simu::MissileHolder> MissileHolderList;       // 导弹实例表[存储具体实例]

        // 前向声明军事目标
        class Target;
        typedef std::shared_ptr<Simu::Target> TargetHolder;     // 自动释放实例资源 
        typedef std::vector<Simu::Target*> TargetList;            // 守方指针列表[提高程序运行效率]
        typedef std::vector<Simu::TargetHolder> TargetHolderList; // 守方实例列表

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

	
	typedef enum DefenceStatus
	{
		DEFENCE_OBJECT_IDLE,		// 空闲状态
		DEFENCE_OBJECT_AWAIT_ORDER,	// 待机发弹
		DEFENCE_OBJECT_LAUNCH_MISSILE	// 发射导弹
	} DefenceStatus;	// 定义防守方状态

	class DefenceObject : public MilitaryObject, public MovingObject
	{
	public:
		DefenceObject();
		DefenceObject(const DefenceObject& defence);
		DefenceObject(const unsigned number, const Simu::Position& pos, const unsigned missiles, 
			      const catype radius, const DefenceStatus status, 
			      const Simu::TargetList& tlist);

		void SetObjectMissileNumber(const unsigned missiles);
		void SetObjectActionRadius(const catype radius);
		void SetObjectStatus(const DefenceStatus status);
		void SetObjectTargetList(const Simu::TargetList& tlist);
		void SetObjectBomberList(const Simu::BomberList& blist);
		unsigned GetObjectMissileNumber() const;
		catype GetObjectActionRadius() const;
		DefenceStatus GetObjectStatus() const;
		Simu::TargetList& GetObjectTargetList();
		Simu::MissileHolderList& GetObjectMissileHolderList();
		Simu::BomberList& GetObjectBomberList();

		// 

		// 时间更新
		void TimeUpdate();

		// 状态记录
		void StatusRecord();

		// 状态更新
		void ChangeStatusAwaitOrder();
		void ChangeStatusLaunchMissile();
	protected:
		unsigned m_MissileNumber_;	// 导弹数量
		catype m_ActionRadius_;		// 作战半径
		DefenceStatus m_Status_;	// 防守方状态

		Simu::TargetList m_TargetList_;			// 守护的军事目标列表
		Simu::MissileHolderList m_MissileHolderList_;	// 导弹列表
		Simu::BomberList m_BomberList_;			// 轰炸机列表
	};	// class DefenceObject

}	// namespace Simu


#endif	// DEFENCE_INCLUDED
