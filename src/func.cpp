#include "func.h"
#include "common.h"

namespace Simu
{

	// 显示程序使用方法
	void ShowUsage(int argc, char* argv[])
        {
                std::cout << "Usage: " << argv[0] << " -se seed -sp speed -e explosion_range -n missile_number" << std::endl;
                std::cout << "       " << "-se  " << "it's an unsigned number that prevent the same running result." << std::endl;
                std::cout << "       " << "-sp  " << "it's a float point number that limit the speed of missiles." << std::endl;
                std::cout << "       " << "-e   " << "it's a float point number that limit the explosion range of missiles." << std::endl;
                std::cout << "       " << "-n   " << "it's an unsigned number that limit the number of missiles of the defence object." << std::endl;
        }

	// 解析参数, 获得模拟初始参数
        bool AnalyzeArguments(int argc, char* argv[])
	{
		try
		{	
			char flag = 0x00;

			for(int i = 1; i < argc; i += 2)
			{
				// 解析随机数种子
				if("-se" == std::string(argv[i]) && !(flag & 0x01))
				{
					Simu::g_Seed = boost::lexical_cast<unsigned>(argv[i + 1]);
					flag |= 0x01;
					continue;
				}

				// 解析导弹航速
				if("-sp" == std::string(argv[i]) && !(flag & 0x02))
				{
					Simu::g_Speed = boost::lexical_cast<catype>(argv[i + 1]);
					flag |= 0x02;
					continue;
				}

				// 解析导弹爆炸范围
				if("-e" == std::string(argv[i]) && !(flag & 0x04))
				{
					Simu::g_ExplosionRange = boost::lexical_cast<catype>(argv[i + 1]);
					flag |= 0x04;
					continue;
				}

				// 解析守方导弹数目
				if("-n" == std::string(argv[i]) && !(flag & 0x08))
				{
					Simu::g_MissileNumber = boost::lexical_cast<catype>(argv[i + 1]);
					flag |= 0x08;
					continue;
				}
			}
			
			return flag == 0x0f ? true : false;
		}
		catch(const boost::bad_lexical_cast& e)
		{
			std::cerr << "参数解析失败!" << std::endl;
			return false;
		}
	}

	// 计算速度分量
	Simu::Speed CaculateSpeedComponent(catype magnitude, const Simu::Position& start, const Simu::Position& stop)
	{
		// 速度计算公式：
		// 	theta = arctan((x2 - x1)/(y2 - y1));
		// 	vx = magnitude*sin(theta)*sign(x2 - x1);
		// 	vy = magnitude*cos(theta)*sign(y2 - y1);

		// 重新表示，方便表述
		catype x1 = start.m_PosX_, y1 = start.m_PosY_;
		catype x2 = stop.m_PosX_, y2 = stop.m_PosY_;

		// 计算位移差
		catype diffX = x2 - x1, diffY = y2 - y1;

		// 计算速度符号
		catype signX = diffX > 0 ? 1.0f : -1.0f;
		catype signY = diffY > 0 ? 1.0f : -1.0f;
		
		// 计算方向角
		catype theta = std::atan(std::abs(diffX / diffY));
		
		// 计算速度分量
		catype speedX = signX*magnitude*std::sin(theta);
		catype speedY = signY*magnitude*std::cos(theta);

		return Simu::Speed(speedX, speedY);
	}

	// 计算拦截位置
	Simu::Position CaculateIntersectPosition(const Simu::Position& pStart, const Simu::Speed& v1, const Simu::Position& pStopRadius, const catype v2, const Simu::Position& pStopTgt, const catype radius)
	{
		// 余弦定理
		// c^2 = a^2 + b^2 -2ab*cos(theta)

		// 计算轰炸机航迹与其和守方连线的夹角的余弦cos(theta)
		catype a1 = pStopRadius.Distance(pStopTgt);
		catype b1 = pStart.Distance(pStopTgt);
		catype c1 = pStopRadius.Distance(pStart);

		catype cosTheta = (b1*b1 + c1*c1 - a1*a1) / (2.0f*b1*c1);

		// 速度等式
		// (v2*t)^2 = c1^2 + (v1*t)^2 - 2.0f*c1*(v1*t)*cos(theta)
		// (v2^2 - v1^2)*t^2 + (2.0f*c1*v1*cos(theta))*t - c1^2 = 0

		catype v1Len = v1.Magnitude();
		catype a2 = v2*v2 - v1Len*v1Len, b2 = 2.0f*c1*v1Len*cosTheta, c2 = -1.0f*c1*c1;
		catype deta = b2*b2 - 4.0f*a2*c2;

                catype t1 = -1.0f, t2 = -1.0f, t = -1.0f;
                if(deta >= 0)
                {
                        t1 = (-b2 + std::sqrt(deta)) / (2.0f*a2);
                        t2 = (-b2 - std::sqrt(deta)) / (2.0f*a2);

                	// 取时间大于零的最小者
                	t = t1 < t2 ? t1 : t2;
                	if(t < 0)
                        	t = (t - t1 == 0) ? t2 : t1;

#ifdef DEBUG
                	std::cout << "t1 = " << t1 << "\tt2 = " << t2 << "\tt = " << t << std::endl;
#endif  // DEBUG

                	// 计算相遇位置
                	if(t > 0)
                	{
                        	Simu::Position pos(pStart);
                        	pos.m_PosX_ += v1.m_SpeedX_*t;
                        	pos.m_PosY_ += v1.m_SpeedY_*t;

                        	return pos;
                	}
                	else
                	{
                        	// 最小时间都为负数，无交点
                        	return pStopTgt;
                	}
		}
		else
		{
			// 无解
			return pStopTgt;
		}
	}

        // 计算是否飞到目的地
        bool CaculateIsArrive(const Simu::Position& start, const Simu::Position& dest, const Simu::Position& cur)
	{
		catype v1x = dest.m_PosX_ - start.m_PosX_, v1y = dest.m_PosY_ - start.m_PosY_;
		catype v2x = dest.m_PosX_ - cur.m_PosX_, v2y = dest.m_PosY_ - cur.m_PosY_;

		return (v1x*v2x + v1y*v2y) > 0 ? false : true;
	}

        // 计算是否模拟结束
        bool SimulateIsDone(const Simu::OffenseObjectList& olist, const Simu::DefenceObjectList& dlist)
        {
                for(auto offense : olist)
                {
                        Simu::BomberHolderList bombers = offense->GetObjectBomberHolderList();
                        for(auto bomber : bombers)
                                if(bomber->GetObjectStatus() != Simu::BomberStatus::BOMBER_MISSION_COMPLETE)
                                        return false;
                }

                for(auto defence : dlist)
                {
                        Simu::MissileHolderList missiles = defence->GetObjectMissileHolderList();
                        for(auto missile : missiles)
                                if(missile->GetObjectStatus() != Simu::MissileStatus::MISSILE_MISSION_COMPLETE)
                                        return false;
                }

                return true;
        }

}	// namespace Simu

