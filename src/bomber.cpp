#include "bomber.h"
#include "common.h"
#include "ccommand.h"
#include "func.h"


namespace Simu
{
	
	///////////////////////////////////////
	// 轰炸机的实现
	///////////////////////////////////////

	Bomber::Bomber() :
		Simu::MilitaryObject("轰炸机", "轰炸守方的军事目标", 0), Simu::MovingObject(),
		m_LaunchTime_(0), m_Target_(nullptr), m_SubjectTo_(nullptr), m_Status_(Simu::BomberStatus::BOMBER_WAIT_LAUNCH)
	{}

	Bomber::Bomber(const Bomber& bomber) :
		Simu::MilitaryObject(bomber.m_Name_, bomber.m_Discription_, bomber.m_Number_),
		Simu::MovingObject(bomber.m_Position_, bomber.m_Speed_),
		m_LaunchTime_(bomber.m_LaunchTime_), m_Target_(bomber.m_Target_), m_SubjectTo_(bomber.m_SubjectTo_), m_Status_(bomber.m_Status_)
	{}

	Bomber::Bomber(const unsigned number, const unsigned launch, const Simu::Position& pos, 
		       const Simu::Speed& speed, Simu::Target* target, Simu::OffenseObject* subject, const BomberStatus status) :
		Simu::MilitaryObject("轰炸机", "轰炸敌方的军事目标", number),
		Simu::MovingObject(pos, speed),
		m_LaunchTime_(launch), m_Target_(target), m_SubjectTo_(subject), m_Status_(status)
	{}

	void Bomber::SetObjectLaunchTime(const unsigned launch)
	{
		m_LaunchTime_ = launch;
	}
    
	void Bomber::SetObjectTarget(Target* target)
	{
		m_Target_ = target;
	}

	void Bomber::SetObjectSubjectTo(Simu::OffenseObject* subject)
	{
		m_SubjectTo_ = subject;
	}

	void Bomber::SetObjectStatus(const BomberStatus status)
	{
		m_Status_ = status;
	}

	unsigned Bomber::GetObjectLaunchTime() const
	{
		return m_LaunchTime_;
	}

	Simu::Target* Bomber::GetObjectTarget() const
	{
		return m_Target_;
	}

	Simu::OffenseObject* Bomber::GetObjectSubjectTo()
	{
		return m_SubjectTo_;
	}

	Simu::BomberStatus Bomber::GetObjectStatus() const
	{
		return m_Status_;
	}

	// 时间更新
	void Bomber::TimeUpdate()
	{
		// 记录轰炸机状态
		StatusRecord();

		switch(m_Status_)
		{
		case Simu::BomberStatus::BOMBER_WAIT_LAUNCH:
			m_LaunchTime_ -= Simu::g_UpdateInterval;
			break;
		case Simu::BomberStatus::BOMBER_LEAVE_FOR_TARGET:
			if(!CaculateIsArrive(m_SubjectTo_->GetObjectPosition(), m_Target_->GetObjectPosition(), m_Position_) && 
			   m_Position_.Distance(m_Target_->GetObjectPosition()) > Simu::g_BomberSuccessRadius)
				m_Position_.UpdatePosition(m_Speed_, (catype)Simu::g_UpdateInterval/1000.0f);
			else
			{
				Simu::CommandHolder ret(new Simu::BomberStatusChangedToReturnBaseCommand(this));
				ret->Execute();
			}
			break;
		case Simu::BomberStatus::BOMBER_CRASHED:
			{
				// 发送完成使命命令
				Simu::CommandHolder complete(new Simu::BomberStatusChangedToMissionCompleteCommand(this));
				complete->Execute();
			}
			break;
		case Simu::BomberStatus::BOMBER_RETURN_BASE:
			if(!CaculateIsArrive(m_Target_->GetObjectPosition(), m_SubjectTo_->GetObjectPosition(), m_Position_) &&
			   m_Position_.Distance(m_SubjectTo_->GetObjectPosition()) > Simu::g_BomberSuccessRadius)
				m_Position_.UpdatePosition(m_Speed_, (catype)Simu::g_UpdateInterval/1000.0f);
			else
			{
				Simu::CommandHolder suc(new Simu::BomberStatusChangedToMissionCompleteCommand(this));
				suc->Execute();
			}
			break;
		case Simu::BomberStatus::BOMBER_MISSION_COMPLETE:
			break;
		default:
			break;
		}
	}

	// 状态记录
	void Bomber::StatusRecord()
	{
		std::string status = "";
		switch(m_Status_)
		{
                case Simu::BomberStatus::BOMBER_WAIT_LAUNCH:
			status = "等待起飞命令";
                        break;
                case Simu::BomberStatus::BOMBER_LEAVE_FOR_TARGET:
			status = "前往军事目标";
                        break;
                case Simu::BomberStatus::BOMBER_CRASHED:
			status = "坠毁";
                        break;
                case Simu::BomberStatus::BOMBER_RETURN_BASE:
			status = "返回基地";
                        break;
                case Simu::BomberStatus::BOMBER_MISSION_COMPLETE:
			status = "使命结束";
                        break;
                default:
                        break;
                }

		std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                        "][状态]: " + 
                        "'" + GetObjectName() + 
                        "' 位于" + m_Position_.CurrentPosition() + "\t状态: " + status;
                
                Simu::g_Logger.push_back(log);
	}

	// 状态更新
	void Bomber::ChangeStatusLeaveForTarget()
	{
		m_Status_ = Simu::BomberStatus::BOMBER_LEAVE_FOR_TARGET;
		
		std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) + 
			"][事件]: " +	
			"'" + GetObjectName() + 
			"' 前往目标 '" + boost::lexical_cast<std::string>(m_Target_->GetObjectName()) + boost::lexical_cast<std::string>(m_Target_->GetObjectNumber()) + "'!";
		
		std::cout << log << std::endl;	
		Simu::g_Logger.push_back(log);
	}

	void Bomber::ChangeStatusCrashed()
	{
		// 统计被击中的轰炸机数
		Simu::g_TotalFailedBomberNumber += 1;

		m_Status_ = Simu::BomberStatus::BOMBER_CRASHED;

                std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                        "][事件]: " +
                        "'" + GetObjectName() + 
                        "' 被导弹击中, 坠毁位置: " + m_Position_.CurrentPosition() + 
			", 轰炸守方军事目标 '" + 
			boost::lexical_cast<std::string>(m_Target_->GetObjectName()) + 
			boost::lexical_cast<std::string>(m_Target_->GetObjectNumber()) + "' 的任务失败!";

		std::cout << log << std::endl;	
                Simu::g_Logger.push_back(log);
	}

	void Bomber::ChangeStatusReturnBase()
	{
		m_Status_ = Simu::BomberStatus::BOMBER_RETURN_BASE;

		// 改变飞行方向
		m_Speed_.m_SpeedX_ *= -1.0f;  m_Speed_.m_SpeedY_ *= -1.0f;

                std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                        "][事件]: " +
                        "'" + GetObjectName() +
                        "' 返回基地 '" + 
                        boost::lexical_cast<std::string>(m_SubjectTo_->GetObjectName()) +
                        boost::lexical_cast<std::string>(m_SubjectTo_->GetObjectNumber()) + "'!";
                
		std::cout << log << std::endl;	
                Simu::g_Logger.push_back(log);

	}

	void Bomber::ChangeStatusMissionComplete()
	{
		m_Status_ = Simu::BomberStatus::BOMBER_MISSION_COMPLETE;

                std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                        "][事件]: " +
                        "'" + GetObjectName() + 
                        "' 轰炸守方军事目标 '" + 
                        boost::lexical_cast<std::string>(m_SubjectTo_->GetObjectName()) + 
                        boost::lexical_cast<std::string>(m_SubjectTo_->GetObjectNumber()) + 
			"' 的使命结束!";
                
		std::cout << log << std::endl;	
                Simu::g_Logger.push_back(log);
	}
	
}	// namespace Simu

