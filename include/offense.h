#ifndef OFFENSE_INCLUDED
#define OFFENSE_INCLUDED

#include "utils.h"
#include "miliobj.h"
#include "target.h"
#include "bomber.h"
#include "defence.h"

namespace Simu
{

	/////////////////////////////////////////
	// 攻方的定义
	/////////////////////////////////////////

	// 前向声明攻方
	class OffenseObject;
        typedef std::shared_ptr<Simu::OffenseObject> OffenseObjectHolder;       // 自动释放实例资源
        typedef std::vector<Simu::OffenseObject*> OffenseObjectList;            // 攻方指针列表[提高运行效率]
        typedef std::vector<Simu::OffenseObjectHolder> OffenseObjectHolderList; // 攻方实例列表

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


	class OffenseObject : public Simu::MilitaryObject, public Simu::MovingObject
	{
	public:
		OffenseObject();
		OffenseObject(const OffenseObject& offense);
		OffenseObject(const unsigned number, const Simu::Position& pos, const unsigned batches, 
			      const Simu::TargetList& tlist, const Simu::DefenceObjectList& dlist);

		void SetObjectBatches(const unsigned batches);
		void SetObjectTargetList(const Simu::TargetList& tlist);
		void SetObjectDefenceObjectList(const Simu::DefenceObjectList& dlist);
		unsigned GetObjectBatches() const;
		Simu::TargetList& GetObjectTargetList();
		Simu::BomberHolderList& GetObjectBomberHolderList();
		Simu::DefenceObjectList& GetObjectDefenceObjectList();

		// 统计轰炸机状态
		unsigned GetObjectSpecificStatusBomberNumber(const Simu::BomberStatus status) const;

		// 时间更新
		void TimeUpdate();
		
		// 状态记录
		void StatusRecord();
	protected:
		unsigned m_Batches_;	// 轰炸机的批次数
		
		Simu::TargetList m_TargetList_;			// 待攻击的军事目标列表
		Simu::BomberHolderList m_BomberHolderList_;	// 轰炸机机群列表
		Simu::DefenceObjectList m_DefenceObjectList_;	// 防守方列表
	};	// class OffenseObject

}	// namespace Simu


#endif	// OFFENSE_INCLUDE

