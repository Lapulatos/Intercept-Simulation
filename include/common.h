#ifndef COMMON_INCLUDED
#define COMMON_INCLUDED

#include "simulator.h"
#include "logger.h"
#include "timer.h"

namespace Simu
{

	////////////////////////////////////////
	// 全局变量声明
	////////////////////////////////////////

	// 随机数种子
	extern unsigned g_Seed;

	// 导弹航速
	extern catype g_Speed;
	
	// 导弹爆炸范围
	extern catype g_ExplosionRange;

	// 导弹数目
	extern unsigned g_MissileNumber;

	// 两批轰炸机最长发射时间间隔
	extern const unsigned g_MaxLaunchTimeInterval;

	// 轰炸机最大航速
	extern const unsigned g_BomberSpeedLimit;	// 单位: 单位距离

	// 轰炸机成功判定半径
	extern const unsigned g_BomberSuccessRadius;
	
	// 记录轰炸机的总数
	extern unsigned g_TotalBomberNumber;
	
	// 记录被击中的轰炸机总数
	extern unsigned g_TotalFailedBomberNumber;

	// 记录导弹总数
	extern unsigned g_TotalMissileNumber;
	
	// 记录击中轰炸机的导弹总数
	extern unsigned g_TotalHitBomberNumber;



	// 计时器
	extern Simu::Timer g_Timer;

	// 当前模拟时间
	extern unsigned g_CurrentSimulateTime;	// 单位: 毫秒

	// 模拟更新时间间隔
	extern const unsigned g_UpdateInterval;	// 毫秒




	// 模拟器
	extern Simu::Simulator g_Simulator;



	// 记录器
	extern Simu::Logger g_Logger;

	// 记录缓冲
	extern char g_LogBuffer[1024];



}	// namespace Simu

#endif	// COMMON_INCLUDED
