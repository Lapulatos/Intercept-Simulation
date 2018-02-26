#ifndef FUNC_INCLUDED
#define FUNC_INCLUDED

#include "utils.h"
#include "offense.h"
#include "defence.h"

namespace Simu
{

	///////////////////////////////////////////
	// 普通函数定义
	/////////////////////////////////////////// 

	// 显示程序使用方法
	void ShowUsage(int argc, char* argv[]);

	// 解析参数, 获得模拟初始参数
	bool AnalyzeArguments(int argc, char* argv[]);

	// 计算速度分量大小
	Simu::Speed CaculateSpeedComponent(catype magnitude, const Simu::Position& start, const Simu::Position& stop);

	// 计算交点
	Simu::Position CaculateIntersectPosition(const Simu::Position& pStart, const Simu::Speed& v1, const Simu::Position& pStopRadius, const catype v2, const Simu::Position& pStopTgt, const catype radius);

	// 计算是否飞到目的地
	bool CaculateIsArrive(const Simu::Position& start, const Simu::Position& dest, const Simu::Position& cur);

	// 计算是否模拟结束
	bool SimulateIsDone(const Simu::OffenseObjectList& olist, const Simu::DefenceObjectList& dlist);

}	// namespace Simu

#endif	// FUNC_INCLUDED
