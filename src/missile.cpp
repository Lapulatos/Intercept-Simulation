#include "missile.h"
#include "common.h"
#include "ccommand.h"


namespace Simu
{

	//////////////////////////////////
	// 导弹的实现
	//////////////////////////////////

	Missile::Missile() :
		Simu::MilitaryObject("导弹", "拦截攻方的轰炸机", 0), Simu::MovingObject(),
		m_ExplosionRange_(0.0f), m_SubjectTo_(nullptr), 
		m_Bomber_(nullptr), m_Status_(Simu::MissileStatus::MISSILE_WAIT_LAUNCH)
	{}

	Missile::Missile(const Missile& missile) :
		Simu::MilitaryObject(missile.m_Name_, missile.m_Discription_, missile.m_Number_),
		Simu::MovingObject(missile.m_Position_, missile.m_Speed_),
		m_ExplosionRange_(missile.m_ExplosionRange_), 
		m_SubjectTo_(missile.m_SubjectTo_), m_Bomber_(missile.m_Bomber_), m_Status_(missile.m_Status_)
	{}

	Missile::Missile(const unsigned number, const Simu::Position& pos, const Simu::Speed& speed, 
		const catype range, Simu::DefenceObject* subject,
		Simu::Bomber* bomber, const MissileStatus status) :
		Simu::MilitaryObject("导弹", "拦截攻方的轰炸机", number),
		Simu::MovingObject(pos, speed),
		m_ExplosionRange_(range), m_SubjectTo_(subject), m_Bomber_(bomber), m_Status_(status)
	{}

	void Missile::SetObjectExplosionRange(const catype range)
	{
		m_ExplosionRange_ = range;
	}

	void Missile::SetObjectSubjectTo(Simu::DefenceObject* subject)
	{
		m_SubjectTo_ = subject;
	}

	void Missile::SetObjectBomber(Simu::Bomber* bomber)
	{
		m_Bomber_ = bomber;
	}

	void Missile::SetObjectStatus(const MissileStatus status)
	{
		m_Status_ = status;
	}

	catype Missile::GetObjectExplosionRange() const
	{
		return m_ExplosionRange_;
	}

	Simu::DefenceObject* Missile::GetObjectSubjectTo() const
	{
		return m_SubjectTo_;
	}

	Simu::Bomber* Missile::GetObjectBomber() const
	{
		return m_Bomber_;
	}

	MissileStatus Missile::GetObjectStatus() const
	{
		return m_Status_;
	}

        // 时间更新
        void Missile::TimeUpdate()
        {
		switch(m_Status_)
		{
		case Simu::MissileStatus::MISSILE_WAIT_LAUNCH:
			break;
		case Simu::MissileStatus::MISSILE_FLIGHTING:
			// 更新导弹位置
			m_Position_.UpdatePosition(m_Speed_, (catype)Simu::g_UpdateInterval/1000.0f);

			// 检查导弹是否飞出作战范围
			if(this->GetObjectPosition().Distance(m_SubjectTo_->GetObjectPosition()) > m_SubjectTo_->GetObjectActionRadius())
			{
				Simu::CommandHolder out(new Simu::MissileStatusChangedToOutActionRadiusCommand(this));
				out->Execute();
			}

			// 检查轰炸机是否到达导弹的爆炸范围
			if(this->GetObjectPosition().Distance(m_Bomber_->GetObjectPosition()) <= m_ExplosionRange_)
			{
				// 随机得到导弹拦截结果
				bool success = (bool)(std::rand() % 2);

				// 拦截成功
				if(success)
				{
					// 向轰炸机发送坠毁命令	
					Simu::CommandHolder crash(new Simu::BomberStatusChangedToCrashedCommand(m_Bomber_));
					crash->Execute();

					// 向自身发送击中命令
					Simu::CommandHolder hit(new Simu::MissileStatusChangedToHitBomberCommand(this));
					hit->Execute();
				}
				else
				{
					Simu::CommandHolder miss(new Simu::MissileStatusChangedToMissedCommand(this));
					miss->Execute();
				}
			}
			//m_Position_.UpdatePosition(m_Speed_);
			break;
		case Simu::MissileStatus::MISSILE_HIT_BOMBER:
		case Simu::MissileStatus::MISSILE_MISSED:
		case Simu::MissileStatus::MISSILE_OUT_ACTION_RADIUS:
			{
            			Simu::CommandHolder await(new Simu::DefenceObjectStatusChangedToAwaitOrderCommand(m_SubjectTo_));
				await->Execute();
            			Simu::CommandHolder complete(new Simu::MissileStatusChangedToMissionCompleteCommand(this));
				complete->Execute();
			}
			break;
		case Simu::MissileStatus::MISSILE_MISSION_COMPLETE:
			break;
		default:
			break;
		}
	}
	
	// 状态记录
	void Missile::StatusRecord() 
	{
		
	}

	// 状态更新
	void Missile::ChangeStatusFlighting()
	{
		m_Status_ = Simu::MissileStatus::MISSILE_FLIGHTING;

                std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                        "][事件]: " +
                        "'" + GetObjectName() +
                        "' 开始拦截轰炸机 '" + m_Bomber_->GetObjectName() + 
                        "'!";
                
		std::cout << log << std::endl;	
                Simu::g_Logger.push_back(log);
	}

	void Missile::ChangeStatusHitBomber()
	{
                // 统计击中轰炸机的导弹总数
                Simu::g_TotalHitBomberNumber += 1;

		m_Status_ = Simu::MissileStatus::MISSILE_HIT_BOMBER;

                std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                        "][事件]: " +
                        "'" + GetObjectName() +
			"' 在坐标: " + m_Position_.CurrentPosition() + 
                        "处成功拦截轰炸机 '" + m_Bomber_->GetObjectName() +
                        "'!";
                
                std::cout << log << std::endl;
                Simu::g_Logger.push_back(log);
	}

	void Missile::ChangeStatusMissed()
	{
		m_Status_ = Simu::MissileStatus::MISSILE_MISSED;

                std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                        "][事件]: " +
                        "'" + GetObjectName() +
                        "' 在坐标: " + m_Position_.CurrentPosition() + 
                        "处拦截轰炸机 '" + m_Bomber_->GetObjectName() +
                        "' 失败!";
                
                std::cout << log << std::endl;          
                Simu::g_Logger.push_back(log);
	}

	void Missile::ChangeStatusOutActionRadius()
	{
		m_Status_ = Simu::MissileStatus::MISSILE_OUT_ACTION_RADIUS;


                std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                        "][事件]: " +
                        "'" + GetObjectName() +
                        "飞出了作战范围!'";
                
                std::cout << log << std::endl;          
                Simu::g_Logger.push_back(log);
	}

	void Missile::ChangeStatusMissionComplete()
	{
		m_Status_ = Simu::MissileStatus::MISSILE_MISSION_COMPLETE;

                std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                        "][事件]: " +
                        "'" + GetObjectName() +
                        "' 拦截轰炸机 '" + m_Bomber_->GetObjectName() + 
                        "' 的使命结束!";
                
                std::cout << log << std::endl;          
                Simu::g_Logger.push_back(log);
	}

}	// namespace Simu
