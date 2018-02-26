#include "utils.h"
#include "common.h"
#include "offense.h"
#include "defence.h"
#include "missile.h"
#include "bomber.h"
#include "timer.h"
#include "simulator.h"
#include "func.h"

int main(int argc, char* argv[])
{
	
	// 检查参数个数
	if(argc < 9)
		Simu::ShowUsage(argc, argv);
	else
	{
		// 解析参数, 获得模拟初始参数
		if(Simu::AnalyzeArguments(argc, argv))
		{
			// 设置显示精度
			std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(4);

			// 初始化随机数生成器
			std::srand(Simu::g_Seed);

#ifdef DEBUG
			std::cout << "Simu::g_Seed = " << Simu::g_Seed << ", Simu::g_Speed = " << Simu::g_Speed << ", Simu::g_ExplosionRange = " << Simu::g_ExplosionRange << ", Simu::g_MissileNumber = " << Simu::g_MissileNumber << std::endl; 
#endif	// DEBUG

			//////////////////////////////////
			// 初始化运行环境
			//////////////////////////////////

			// 定义守方军事目标
        		Simu::Target t1(1, Simu::Position(43.0f, 34.0f), Simu::TargetStatus::TARGET_UNDAMAGED);
        		Simu::Target t2(2, Simu::Position(38.0f, 14.0f), Simu::TargetStatus::TARGET_UNDAMAGED);

        		// 定义军事目标列表
        		Simu::TargetList tlist, tlist1, tlist2;
        		tlist.push_back(&t1); tlist.push_back(&t2);
        		tlist1.push_back(&t1);
        		tlist2.push_back(&t1); tlist2.push_back(&t2);

        		// 定义守方
        		catype radius = 15.0f;
        		Simu::DefenceObject d1(1, Simu::Position(44.0f, 41.0f), Simu::g_MissileNumber, radius, Simu::DefenceStatus::DEFENCE_OBJECT_IDLE, tlist1);
        		Simu::DefenceObject d2(2, Simu::Position(42.0f, 20.0f), Simu::g_MissileNumber, radius, Simu::DefenceStatus::DEFENCE_OBJECT_IDLE, tlist2);

        		// 定义守方列表
        		Simu::DefenceObjectList dlist, dlist1, dlist2;
        		dlist.push_back(&d1); dlist.push_back(&d2);
        		dlist1.push_back(&d1);
        		dlist2.push_back(&d1); dlist2.push_back(&d2);

			// 设置军事目标受保护表
			t1.SetObjectProtectedBy(dlist1);
			t2.SetObjectProtectedBy(dlist2);

        		// 定义攻方
        		unsigned batches1 = 1, batches2 = 2;
        		Simu::OffenseObject o1(1, Simu::Position(12.0f, 39.0f), batches1, tlist1, dlist);
        		Simu::OffenseObject o2(2, Simu::Position(9.0f, 14.0f), batches2, tlist2, dlist);

        		// 定义攻方列表
        		Simu::OffenseObjectList olist, olist1, olist2;
        		olist.push_back(&o1); olist.push_back(&o2);
        		olist1.push_back(&o1);
        		olist2.push_back(&o2);

			// 添加
        		Simu::g_Timer.SetOffenseObjectList(olist);
        		Simu::g_Timer.SetDefenceObjectList(dlist);
        		Simu::g_Timer.SetTargetList(tlist);

			//////////////////////////////////
			// 开始模拟
			//////////////////////////////////
			
			while(!SimulateIsDone(olist, dlist))
			{
				Simu::g_Timer.TimeUpdate();
				Simu::g_Simulator.ExecuteCommands();
				Simu::g_CurrentSimulateTime += Simu::g_UpdateInterval;
				
		//		std::cout << "-----------------------------------------------------------" << std::endl;

                        //	Simu::g_Timer.TimeUpdate();
                        //	Simu::g_Simulator.Notify();
                        //	Simu::g_CurrentSimulateTime += Simu::g_UpdateInterval;
			}

			// 计算模拟结果
			unsigned bomberSuc = Simu::g_TotalBomberNumber - Simu::g_TotalFailedBomberNumber;
			catype missileSucRatio = ((catype)Simu::g_TotalHitBomberNumber / Simu::g_TotalBomberNumber) * 100.0f;

			// 显示模拟结果
			std::cout << "-----------------------------------------------" << std::endl;
			
			std::cout << "轰炸机总数: " << Simu::g_TotalBomberNumber << std::endl
				<< "导弹总数: " << Simu::g_TotalMissileNumber << std::endl
				<< "轰炸机击落数: " << Simu::g_TotalFailedBomberNumber << std::endl
				<< "干扰成功次数: " << bomberSuc << std::endl 
				<< "拦截成功次数: " << Simu::g_TotalHitBomberNumber << std::endl
				<< "拦截成功率: " << missileSucRatio << "%" << std::endl;
		}
		else
		{
			std::cerr << "参数设置不正确!" << std::endl;
		}
	}	

	return 0;
}

