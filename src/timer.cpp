#include "timer.h"
#include "command.h"
#include "ccommand.h"
#include "common.h"

namespace Simu
{
    	// 声明模拟器全局变量
	//extern Simu::Simulator g_Simulator;
    
    	Timer::Timer()
   	{}
    
    	Timer::Timer(const Timer& timer) :
        	m_OffenseObjectList_(timer.m_OffenseObjectList_), m_DefenceObjectList_(timer.m_DefenceObjectList_),
        	m_MissileList_(timer.m_MissileList_), m_BomberList_(timer.m_BomberList_), m_TargetList_(timer.m_TargetList_)
    	{}
    
	Timer::Timer(const Simu::OffenseObjectList& olist,
		     const Simu::DefenceObjectList& dlist,
	      	     const Simu::MissileList& mlist,
		     const Simu::BomberList& blist,
          	     const Simu::TargetList& tlist) :
        	m_OffenseObjectList_(olist), m_DefenceObjectList_(dlist),
        	m_MissileList_(mlist), m_BomberList_(blist), m_TargetList_(tlist)
    	{}
		
	void Timer::AddOffenseObject(Simu::OffenseObject* offense)
    	{
        	m_OffenseObjectList_.push_back(offense);
    	}
    
	void Timer::AddDefenceObject(Simu::DefenceObject* defence)
    	{
        	m_DefenceObjectList_.push_back(defence);
    	}
    
	void Timer::AddMissile(Simu::Missile* missile)
    	{
        	m_MissileList_.push_back(missile);
    	}
    
	void Timer::AddBomber(Simu::Bomber* bomber)
    	{
        	m_BomberList_.push_back(bomber);
    	}
    
	void Timer::AddTarget(Simu::Target* target)
    	{
        	m_TargetList_.push_back(target);
    	}

	void Timer::RemoveOffenseObject(Simu::OffenseObject* offense)
    	{
        	for(Simu::OffenseObjectList::iterator it = m_OffenseObjectList_.begin(); it != m_OffenseObjectList_.end(); ++it)
        	{
            		// 指针相同
            		if(*it == offense)
            		{
                		m_OffenseObjectList_.erase(it);
                		break;
            		}
        	}
    	}
    
	void Timer::RemoveDefenceObject(Simu::DefenceObject* defence)
    	{
        	for(Simu::DefenceObjectList::iterator it = m_DefenceObjectList_.begin(); it != m_DefenceObjectList_.end(); ++it)
        	{
            		// 指针相同
            		if(*it == defence)
            		{
                		m_DefenceObjectList_.erase(it);
                	break;
            		}
        	}
    	}
    
	void Timer::RemoveMissile(Simu::Missile* missile)
    	{
        	for(Simu::MissileList::iterator it = m_MissileList_.begin(); it != m_MissileList_.end(); ++it)
        	{
            		// 指针相同
            		if(*it == missile)
            		{
                		m_MissileList_.erase(it);
                		break;
            		}
        	}
    	}
    
	void Timer::RemoveBomber(Simu::Bomber* bomber)
    	{
        	for(Simu::BomberList::iterator it = m_BomberList_.begin(); it != m_BomberList_.end(); ++it)
        	{
            		// 指针相同
            		if(*it == bomber)
            		{
                		m_BomberList_.erase(it);
                		break;
            		}
        	}
    	}
    
	void Timer::RemoveTarget(Simu::Target* target)
    	{
        	for(Simu::TargetList::iterator it = m_TargetList_.begin(); it != m_TargetList_.end(); ++it)
        	{
            		// 指针相同
            		if(*it == target)
            		{
                		m_TargetList_.erase(it);
                		break;
            		}
        	}
    	}

	void Timer::SetOffenseObjectList(const Simu::OffenseObjectList& olist)
	{
		m_OffenseObjectList_ = olist;
	}

	void Timer::SetDefenceObjectList(const Simu::DefenceObjectList& dlist)
	{
		m_DefenceObjectList_ = dlist;
	}

	void Timer::SetMissileList(const Simu::MissileList& mlist)
	{
		m_MissileList_ = mlist;
	}

	void Timer::SetBomberList(const Simu::BomberList& blist)
	{
		m_BomberList_ = blist;
	}

	void Timer::SetTargetList(const Simu::TargetList& tlist)
	{
		m_TargetList_ = tlist;
	}

	Simu::OffenseObjectList& Timer::GetOffenseObjectList()
    	{
        	return m_OffenseObjectList_;
    	}
    
	Simu::DefenceObjectList& Timer::GetDefenceObjectList()
    	{
        	return m_DefenceObjectList_;
    	}
    
	Simu::MissileList& Timer::GetMissileList()
    	{
        	return m_MissileList_;
    	}
    
	Simu::BomberList& Timer::GetBomberList()
    	{
        	return m_BomberList_;
    	}
    
	Simu::TargetList& Timer::GetTargetList()
    	{
        	return m_TargetList_;
    	}
    
    	void Timer::TimeUpdate()
    	{
        	// 对每个列表中的对象发出时间更新命令
        
        	// 对攻方列表中所有对象发出时间更新命令
        	//for(auto offense : m_OffenseObjectList_)
		//{
            	//	Simu::g_Simulator.AddCommand(new OffenseTimeUpdateCommand(offense));
		//}        

        	// 对导弹列表中所有对象发出时间更新命令
        	for(auto missile : m_MissileList_)
		{
            		g_Simulator.AddCommand(new MissileTimeUpdateCommand(missile));
                }

                // 对守方列表中所有对象发出时间更新命令
                for(auto defence : m_DefenceObjectList_)
                {
                        g_Simulator.AddCommand(new DefenceTimeUpdateCommand(defence));
                }

        	// 对轰炸机机群列表中所有对象发出时间更新命令
        	for(auto bomber : m_BomberList_)
		{
            		g_Simulator.AddCommand(new BomberTimeUpdateCommand(bomber));
                }

        	// 对守方军事目标列表中所有对象发出时间更新命令
        	for(auto target : m_TargetList_)
		{
            		g_Simulator.AddCommand(new TargetTimeUpdateCommand(target));
                }

                // 对攻方列表中所有对象发出时间更新命令
                for(auto offense : m_OffenseObjectList_)
                {
                        Simu::g_Simulator.AddCommand(new OffenseTimeUpdateCommand(offense));
                }
    	}
    
}   // namespace Simu
