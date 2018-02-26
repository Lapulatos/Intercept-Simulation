#ifndef TIMER_INCLUDED
#define TIMER_INCLUDED

#include "offense.h"
#include "defence.h"
#include "missile.h"
#include "bomber.h"
#include "target.h"


namespace Simu
{

	/////////////////////////////////////////////
	// 定时器的定义
	//
	//    定时器用于推动模拟的进行
	/////////////////////////////////////////////

	class Timer
	{
	public:
		Timer();
		Timer(const Timer& timer);
        	Timer(const Simu::OffenseObjectList& olist,
		      const Simu::DefenceObjectList& dlist,
		      const Simu::MissileList& mlist,
		      const Simu::BomberList& blist,
		      const Simu::TargetList& tlist);
        
		void AddOffenseObject(Simu::OffenseObject* offense);
		void AddDefenceObject(Simu::DefenceObject* defence);
		void AddMissile(Simu::Missile* missile);
		void AddBomber(Simu::Bomber* bomber);
		void AddTarget(Simu::Target* target);

		void RemoveOffenseObject(Simu::OffenseObject* offense);
		void RemoveDefenceObject(Simu::DefenceObject* defence);
		void RemoveMissile(Simu::Missile* missile);
		void RemoveBomber(Simu::Bomber* bomber);
		void RemoveTarget(Simu::Target* target);

        	void SetOffenseObjectList(const Simu::OffenseObjectList& olist);
        	void SetDefenceObjectList(const Simu::DefenceObjectList& dlist);
        	void SetMissileList(const Simu::MissileList& mlist);
        	void SetBomberList(const Simu::BomberList& blist);
        	void SetTargetList(const Simu::TargetList& tlist);
        
		Simu::OffenseObjectList& GetOffenseObjectList();
		Simu::DefenceObjectList& GetDefenceObjectList();
		Simu::MissileList& GetMissileList();
		Simu::BomberList& GetBomberList();
		Simu::TargetList& GetTargetList();

		// 总的模拟时间推进过程
		void TimeUpdate();

	protected:
		Simu::OffenseObjectList m_OffenseObjectList_;
		Simu::DefenceObjectList m_DefenceObjectList_;
		Simu::MissileList m_MissileList_;
		Simu::BomberList m_BomberList_;
		Simu::TargetList m_TargetList_;
	};	// class Timer

}	// namespace Simu


#endif	// TIMER_INCLUDED
