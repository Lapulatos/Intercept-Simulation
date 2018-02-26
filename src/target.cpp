#include "target.h"

namespace Simu
{

	// the implementation of Target
	Target::Target() :
		Simu::MilitaryObject("军事目标", "该目标需要受到守方的保护", 0), Simu::MovingObject(), 
		m_ProtectedBy_(), m_Status_(Simu::TargetStatus::TARGET_UNDAMAGED)
	{}

	Target::Target(const Target& target) :
		Simu::MilitaryObject(target.m_Name_, target.m_Discription_, target.m_Number_),
		Simu::MovingObject(target.m_Position_, target.m_Speed_), 
		m_ProtectedBy_(target.m_ProtectedBy_), m_Status_(target.m_Status_)
	{}

	Target::Target(const unsigned number, const Simu::Position& pos, const TargetStatus status) :
		Simu::MilitaryObject("军事目标", "该目标需要受到守方的保护", number), 
		Simu::MovingObject(Simu::Position(pos), Simu::Speed()), 
		m_ProtectedBy_(), m_Status_(status)
	{}

	void Target::SetObjectProtectedBy(const Simu::DefenceObjectList& plist)
	{
		m_ProtectedBy_ = plist;
	}

	void Target::SetObjectStatus(const TargetStatus status)
	{
		m_Status_ = status;
	}

	Simu::DefenceObjectList& Target::GetObjectProtectedBy()
	{
		return m_ProtectedBy_;
	}

	TargetStatus Target::GetObjectStatus() const
	{
		return m_Status_;
	}

        // 时间更新
        void Target::TimeUpdate()
        {
		// do nothing	
	}

	// 状态记录
	void Target::StatusRecord()
	{
	}

	// 状态更新
	void Target::ChangeStatusDestroyed()
	{
		m_Status_ = Simu::TargetStatus::TARGET_DESTROYED;
		std::cout << GetObjectName() << GetObjectNumber() << " 已被摧毁！" << std::endl;
	}

}	// namespace Simu
