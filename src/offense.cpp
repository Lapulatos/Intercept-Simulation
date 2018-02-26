#include "offense.h"
#include "ccommand.h"
#include "common.h"
#include "func.h"

namespace Simu
{

	/////////////////////////////////////
	// 攻击方的实现
	/////////////////////////////////////

	OffenseObject::OffenseObject() :
		Simu::MilitaryObject("攻击方", "攻击防守方的军事目标", 0),
		Simu::MovingObject(Simu::Position(), Simu::Speed()),
		m_Batches_(0)
	{}

	OffenseObject::OffenseObject(const OffenseObject& offense) :
		Simu::MilitaryObject(offense.m_Name_, offense.m_Discription_, offense.m_Number_),
		Simu::MovingObject(offense.m_Position_, offense.m_Speed_),
		m_TargetList_(offense.m_TargetList_), m_DefenceObjectList_(offense.m_DefenceObjectList_),
		m_Batches_(offense.m_Batches_)
	{
		// copy bomber holder list
		for(auto bomber : offense.m_BomberHolderList_)
			m_BomberHolderList_.push_back(Simu::BomberHolder(new Simu::Bomber(*bomber)));
	}

	OffenseObject::OffenseObject(const unsigned number, const Simu::Position& pos, const unsigned batches,
		const Simu::TargetList& tlist, const Simu::DefenceObjectList& dlist) :
		Simu::MilitaryObject("攻击方", "攻击防守方的军事目标", number),
		Simu::MovingObject(pos, Simu::Speed()),
		m_TargetList_(tlist), m_DefenceObjectList_(dlist),
		m_Batches_(batches)
	{
		// 记录上一批次轰炸机的发射时间
		unsigned lastLaunch = 0;

		// 随机创建多批轰炸机
		for(unsigned i = 0; i < m_Batches_; ++i)
		{
			// 随机生成轰炸机机群规模
			unsigned scale = (std::rand() % 4 + 1) * 2;	// 生成2~8之间的偶数

			// 统计总的轰炸机数
			Simu::g_TotalBomberNumber += scale;
			
			// 随机指定攻击的守方军事目标
			unsigned index = std::rand() % m_TargetList_.size();
			Simu::Target* target = m_TargetList_[index];

			// 随机生成起飞时间
			unsigned launch = lastLaunch + std::rand() % Simu::g_MaxLaunchTimeInterval;
			launch -= launch % Simu::g_UpdateInterval;	// 去除余数
			lastLaunch = launch;

			// 随机生成航速
			catype speedMagnitude = std::rand() % Simu::g_BomberSpeedLimit + 1;
			
			// 计算速度分量
			Simu::Speed speed = CaculateSpeedComponent(speedMagnitude, GetObjectPosition(), target->GetObjectPosition());

#ifdef	DEBUG
			std::cout << GetObjectName() << GetObjectNumber() << " pos:" << GetObjectPosition().CurrentPosition() << ": batches[" << i << "]:  scale = " << scale 
				<< ", targetIndex = " << index << ", target: " << target->GetObjectName() << target->GetObjectNumber() << " pos:" << target->GetObjectPosition().CurrentPosition()
				<< ", launch = " << launch << ", speedMagnitude = " << speedMagnitude 
				<< ", speed = " << speed.CurrentSpeed() << " -- " << speed.Magnitude() << std::endl;
#endif	// DEBUG
			
			// 显示初始化配置
                        std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
                        	"][事件]: " +
                                "[" + GetObjectName() + boost::lexical_cast<std::string>(GetObjectNumber()) +
                                "] 指派第" + boost::lexical_cast<std::string>(i + 1) +
				"批, 规模为" + boost::lexical_cast<std::string>(scale) + 
				"的轰炸机机群, 于" + boost::lexical_cast<std::string>(launch) +
				"毫秒后, 以每秒" + boost::lexical_cast<std::string>(speedMagnitude) + 
				"个单位的航速, 轰炸守方的军事目标 '" + target->GetObjectName() + boost::lexical_cast<std::string>(target->GetObjectNumber())+ "'!";

                        std::cout << log << std::endl;
                        Simu::g_Logger.push_back(log);
			

			// 获得轰炸机的位置
			Simu::Position pos = GetObjectPosition();

			// 获得守方目标的保护者
			Simu::DefenceObjectList dlist = target->GetObjectProtectedBy();

			// 随机生成轰炸机
			for(unsigned j = 0; j < scale; ++j)
			{
				Simu::BomberHolder bomber(new Bomber(i+10+j, launch, pos, speed, target, this, Simu::BomberStatus::BOMBER_WAIT_LAUNCH));
				bomber->SetObjectName("轰炸机[" + boost::lexical_cast<std::string>(GetObjectNumber()) + ":" + boost::lexical_cast<std::string>(i + 1) + ":" + boost::lexical_cast<std::string>(j + 1) + "]");			
	
				// 加入守护方监视列表
				for(auto defence : dlist)
					defence->GetObjectBomberList().push_back(&*bomber);
	
				m_BomberHolderList_.push_back(bomber);	// 保存轰炸机实例
				Simu::g_Timer.AddBomber(&*bomber);	// 轰炸机进入状态更新循环中
			}
		}
	}

	void OffenseObject::SetObjectBatches(const unsigned batches)
	{
		m_Batches_ = batches;
	}

	void OffenseObject::SetObjectTargetList(const Simu::TargetList& tlist)
	{
		m_TargetList_ = tlist;
	}

	void OffenseObject::SetObjectDefenceObjectList(const Simu::DefenceObjectList& dlist)
	{
		m_DefenceObjectList_ = dlist;
	}

	unsigned OffenseObject::GetObjectBatches() const
	{
		return m_Batches_;
	}

	Simu::TargetList& OffenseObject::GetObjectTargetList()
	{
		return m_TargetList_;
	}

	Simu::BomberHolderList& OffenseObject::GetObjectBomberHolderList()
	{
		return m_BomberHolderList_;
	}

	Simu::DefenceObjectList& OffenseObject::GetObjectDefenceObjectList()
	{
		return m_DefenceObjectList_;
	}


	// 统计轰炸机状态
	unsigned OffenseObject::GetObjectSpecificStatusBomberNumber(const Simu::BomberStatus status) const
	{
		unsigned number = 0;

		for(auto bomber : m_BomberHolderList_)
			if(bomber->GetObjectStatus() == status)
				++number;

		return number;
	}

	// 时间更新
	void OffenseObject::TimeUpdate()
	{
		// 记录守方状态
		StatusRecord();

		// 检查轰炸机是否可以起飞
		for(auto bomber : m_BomberHolderList_)
		{
			if((bomber->GetObjectLaunchTime() <= 0) && (bomber->GetObjectStatus() == Simu::BomberStatus::BOMBER_WAIT_LAUNCH))	// 炸机可以起飞
			{
				Simu::Target* target = bomber->GetObjectTarget();

                                // 记录事件
				std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) +
					"][事件]: " +
					"'" + GetObjectName() + boost::lexical_cast<std::string>(GetObjectNumber()) +
					"'\t派出了'" + bomber->GetObjectName() + 
					"'轰炸守方目标'" + target->GetObjectName() + boost::lexical_cast<std::string>(target->GetObjectNumber())+ "'!";

				std::cout << log << std::endl;
				Simu::g_Logger.push_back(log);

				// 向轰炸机发送起飞命令
				Simu::CommandHolder launch(new Simu::BomberStatusChangedToLeaveForTargetCommand(&*bomber));
				launch->Execute();

				// 守方进入警戒状态[待机发弹]
				for(auto defence : m_DefenceObjectList_)
				{
                                        if(defence->GetObjectStatus() == Simu::DefenceStatus::DEFENCE_OBJECT_IDLE)
                                        {
                                                Simu::CommandHolder notify(new Simu::DefenceObjectStatusChangedToAwaitOrderCommand(&*defence));
                                                notify->Execute();
                                        } 
				}
			}
		}
	}

	// 状态记录
	void OffenseObject::StatusRecord()
	{
		std::string log = "[时间:" + boost::lexical_cast<std::string>(Simu::g_CurrentSimulateTime) + 
			"][状态]: "
			"'" + GetObjectName() + boost::lexical_cast<std::string>(GetObjectNumber()) + 
			"': 位置: " + m_Position_.CurrentPosition() + 
			"\t待命: " + boost::lexical_cast<std::string>(GetObjectSpecificStatusBomberNumber(Simu::BomberStatus::BOMBER_WAIT_LAUNCH)) +
			"\t起飞: " + boost::lexical_cast<std::string>(GetObjectSpecificStatusBomberNumber(Simu::BomberStatus::BOMBER_LEAVE_FOR_TARGET)) +
			"\t坠毁: " + boost::lexical_cast<std::string>(GetObjectSpecificStatusBomberNumber(Simu::BomberStatus::BOMBER_CRASHED)) +
			"\t返航: " + boost::lexical_cast<std::string>(GetObjectSpecificStatusBomberNumber(Simu::BomberStatus::BOMBER_RETURN_BASE)) +
			"\t完成: " + boost::lexical_cast<std::string>(GetObjectSpecificStatusBomberNumber(Simu::BomberStatus::BOMBER_MISSION_COMPLETE));

		Simu::g_Logger.push_back(log);
	}

}	// namespace Simu

