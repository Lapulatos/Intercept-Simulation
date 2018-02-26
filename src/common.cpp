#include "common.h"

namespace Simu
{

	/////////////////////////////////////////
	// 全局变量定义
	/////////////////////////////////////////

	// 随机数种子
	unsigned g_Seed;

        // 导弹航速
        catype g_Speed = (catype)0.0f;

        // 导弹爆炸范围
        catype g_ExplosionRange = (catype)0.0f;

        // 导弹数目
        unsigned g_MissileNumber = 0;

        // 两批轰炸机最长发射时间间隔
        const unsigned g_MaxLaunchTimeInterval = 60000;	// 60秒

	// 轰炸机最大航速
	const unsigned g_BomberSpeedLimit = 3;	// 三个距离单位/秒

	// 轰炸机成功判定半径
	const unsigned g_BomberSuccessRadius = 1;


        // 记录轰炸机的总数
        unsigned g_TotalBomberNumber = 0;

        // 记录被击中的轰炸机总数
        unsigned g_TotalFailedBomberNumber = 0;

        // 记录导弹总数
        unsigned g_TotalMissileNumber = 0;

        // 记录击中轰炸机的导弹总数
        unsigned g_TotalHitBomberNumber = 0;

	

        // 计时器
        Simu::Timer g_Timer;

        // 当前模拟时间
        unsigned g_CurrentSimulateTime = 0;	// 单位毫秒

        // 模拟更新时间间隔
        const unsigned g_UpdateInterval = 1000;	// 毫秒



	// 模拟器
	Simu::Simulator g_Simulator;

	// 记录器
	Simu::Logger g_Logger("simulate.log");

	// 记录缓冲
	char g_LogBuffer[1024];
	
}	// namespace Simu
