#include "defence.h"
#include "common.h"
#include "func.h"
#include "ccommand.h"


namespace Simu
{

	//////////////////////////////////////
	// 防守方的实现
	//////////////////////////////////////

	DefenceObject::DefenceObject() :
		Simu::MilitaryObject("防守方", "保护军事目标不被攻方轰炸", 0),
		Simu::MovingObject(),
		m_MissileNumber_(0), m_ActionRadius_(0.0f), m_Status_(Simu::DefenceStatus::DEFENCE_OBJECT_IDLE)
	{}

	DefenceObject::DefenceObject(const DefenceObject& defence) :
		Simu::MilitaryObject(defence.m_Name_, defence.m_Discription_, defence.m_Number_),
		Simu::MovingObject(defence.m_Position_, Simu::Speed()),
		m_MissileNumber_(defence.m_MissileNumber_), 
		m_ActionRadius_(defence.m_ActionRadius_), m_Status_(defence.m_Status_),
		m_TargetList_(defence.m_TargetList_)
	{
		// 统计导弹总数
		Simu::g_TotalMissileNumber += m_MissileNumber_;
		
		// copy missile holder list
		for(auto missile : defence.m_MissileHolderList_)
			m_MissileHolderList_.push_back(Simu::MissileHolder(new Simu::Missile(*missile)));
	}

	DefenceObject::DefenceObject(const unsigned number, const Simu::Position& pos, 
				     const unsigned missiles, const catype radius, 
				     const Simu::DefenceStatus status, const Simu::TargetList& tlist) :
		Simu::MilitaryObject("防守方", "保护军事目标不被攻方轰炸", number),
		Simu::MovingObject(pos, Simu::Speed()),
		m_MissileNumber_(missiles), m_ActionRadius_(radius), m_Status_(status),
		m_TargetList_(tlist)
	{
                // 统计导弹总数
                Simu::g_TotalMissileNumber += m_MissileNumber_;
	}

	void DefenceObject::SetObjectMissileNumber(const unsigned missiles)
	{
		m_MissileNumber_ = missiles;
	}

	void DefenceObject::SetObjectActionRadius(const catype radius)
	{
		m_ActionRadius_ = radius;
	}

	void DefenceObject::SetObjectStatus(const Simu::DefenceStatus status)
	{
		m_Status_ = status;
	}

	void DefenceObject::SetObjectTargetList(const Simu::TargetList& tlist)
	{
		m_TargetList_ = tlist;
	}

	void DefenceObject::SetObjectBomberList(const Simu::BomberList& blist)
	{
		m_BomberList_ = blist;
	}

	unsigned DefenceObject::GetObjectMissileNumber() const
	{
		return m_MissileNumber_;
	}

	catype DefenceObject::GetObjectActionRadius() const
	{
		return m_ActionRadius_;
	}

	Simu::DefenceStatus DefenceObject::GetObjectStatus() const
	{
		return m_Status_;
	}

	Simu::TargetList& DefenceObject::GetObjectTargetList()
	{
		return m_TargetList_;
	}

	Simu::MissileHolderList& DefenceObject::GetObjectMissileHolderList()
	{
		return m_MissileHolderList_;
	}

	Simu::BomberList& DefenceObject::GetObjectBomberList()
	{
		return m_BomberList_;
	}

	// 时间更新
	void DefenceObject::TimeUpdate()
	{
		// 记录守方状态
		StatusRecord();

		switch(m_Status_)
		{
		case Simu::DefenceStatus::DEFENCE_OBJECT_IDLE:
			break;
		case Simu::DefenceStatus::DEFENCE_OBJECT_AWAIT_ORDER:
			// 检查轰炸机是否进入作战范围
			for(auto bomber : m_BomberList_)
			{
				Simu::Position tgtPos = bomber->GetObjectTarget()->GetObjectPosition();	// 获取轰炸机攻击目标位置
				Simu::Position defPos = this->GetObjectPosition();	// 获取守方位置
				Simu::Position bomPos = bomber->GetObjectPosition();	// 获取轰炸机位置

				// 守方还有导弹、轰炸机进入作战范围、轰炸机正前往军事目标或返回基地
				if(m_MissileNumber_ > 0 && bomPos.Distance(defPos) <= m_ActionRadius_ && 
					(bomber->GetObjectStatus() == Simu::BomberStatus::BOMBER_LEAVE_FOR_TARGET || bomber->GetObjectStatus() == Simu::BomberStatus::BOMBER_RETURN_BASE))
				{
					// 检查导弹列表中是否没有正在拦截轰炸机的导弹
					bool noIntercept = true;

					for(auto missile : m_MissileHolderList_)
					{
						Simu::MissileStatus status = missile->GetObjectStatus();

						if(status == Simu::MissileStatus::MISSILE_WAIT_LAUNCH || 	// 有正在等待发射的导弹
						   status == Simu::MissileStatus::MISSILE_FLIGHTING)		// 有正在拦截轰炸机的导弹
						{
							noIntercept = false;
							break;
						}
					}
	
					if(noIntercept)
					{
						// 计算导弹与轰炸机的交点
						Simu::Position itstPos = CaculateIntersectPosition(bomPos, bomber->GetObjectSpeed(), defPos, Simu::g_Speed, tgtPos, defPos.Distance(bomPos));

						// 计算导弹发射时间和速度[方向]
						Simu::Speed speed = CaculateSpeedComponent(Simu::g_Speed, defPos, itstPos);
						
						// 创建导弹对象
						MissileHolder missile(new Missile(m_MissileNumber_--, this->GetObjectPosition(), speed, Simu::g_ExplosionRange, this, bomber, Simu::MissileStatus::MISSILE_FLIGHTING));
						missile->SetObjectName("导弹[" + boost::lexical_cast<std::string>(GetObjectNumber()) + ":" + boost::lexical_cast<std::string>(missile->GetObjectNumber()) + "]");
						m_MissileHolderList_.push_back(missile);
						Simu::g_Timer.AddMissile(&*missile);	// 更新导弹的状态


                                                // 显示事件
                                                std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                                                        "][事件]: " +
                                                        "'" + GetObjectName() + boost::lexical_cast<std::string>(GetObjectNumber()) +
                                                        "'计算出了拦截轰炸机 '" + bomber->GetObjectName() + 
                                                        "' 的拦截位置: " + itstPos.CurrentPosition() + 
                                                        ", 现在发射导弹 '" + missile->GetObjectName() + "' 拦截该轰炸机! ";

                                                std::cout << log << std::endl;
                                                Simu::g_Logger.push_back(log);

						// 自身进入发弹状态
						Simu::CommandHolder launch(new Simu::DefenceObjectStatusChangedToLaunchMissileCommand(this));
						launch->Execute();
					}
				}
			}
			break;
		case Simu::DefenceStatus::DEFENCE_OBJECT_LAUNCH_MISSILE:
			// 检查导弹列表是否有待发射的导弹, 有就直接发
			for(auto missile : m_MissileHolderList_)
			{
				if(missile->GetObjectStatus() == Simu::MissileStatus::MISSILE_WAIT_LAUNCH)
				{
					Simu::CommandHolder launch(new Simu::MissileStatusChangedToFlightingCommand(&*missile));	// 发射导弹
					launch->Execute();
					Simu::CommandHolder await(new Simu::DefenceObjectStatusChangedToAwaitOrderCommand(this));	// 继续警戒
					await->Execute();
					break;
				}
			}
			break;
		default:
			break;
		}
    	}

	// 状态记录
	void DefenceObject::StatusRecord()
	{
		std::string status = "";
	
		switch(m_Status_)
		{
		case Simu::DefenceStatus::DEFENCE_OBJECT_IDLE:
			status = "空闲";
			break;
		case Simu::DefenceStatus::DEFENCE_OBJECT_AWAIT_ORDER:
			status = "待机发射";
			break;
		case Simu::DefenceStatus::DEFENCE_OBJECT_LAUNCH_MISSILE:
			status = "发射导弹";
			break;
		default:
			break;
		}

                std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                        "][状态]: " +
                        "'" + GetObjectName() + boost::lexical_cast<std::string>(GetObjectNumber()) +
                        "'\t位于: " + m_Position_.CurrentPosition() + 
			"\t导弹剩余数: " + boost::lexical_cast<std::string>(m_MissileNumber_) + 
			"\t状态: " + status; 

                Simu::g_Logger.push_back(log);
	}

	// 状态更新
	void DefenceObject::ChangeStatusAwaitOrder()
	{
		m_Status_ = Simu::DefenceStatus::DEFENCE_OBJECT_AWAIT_ORDER;

                std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                        "][事件]: " +
                        "'" + GetObjectName() + boost::lexical_cast<std::string>(GetObjectNumber()) + 
                        "' 进入了待机发射状态!"; 
                
		std::cout << log << std::endl;	
                Simu::g_Logger.push_back(log);
	}

	void DefenceObject::ChangeStatusLaunchMissile()
	{
		m_Status_ = Simu::DefenceStatus::DEFENCE_OBJECT_LAUNCH_MISSILE;

                std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                        "][事件]: " +
                        "'" + GetObjectName() + boost::lexical_cast<std::string>(GetObjectNumber()) +
                        "' 发射了导弹!";
                
                std::cout << log << std::endl;
                Simu::g_Logger.push_back(log);
	}
}	// namespace Simu

