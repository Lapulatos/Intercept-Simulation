#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

// for configurating this program
#include "config.h"

// system header included
#include <iostream>		// 用于输入输出
#include <iomanip>		// 控制显示精度
#include <memory>		// 
#include <cmath>		// 用于轨道计算等数学问题
#include <exception>		// 用于异常处理
#include <string>		// 用于字符串处理
#include <functional>		// 用于其它空能性需求
#include <algorithm>	
#include <cstdlib>		// 用于产生随机数
#include <list>			// 用于保存变量的容器
#include <queue>		// 容器 +1

// thirdpart library included
#include <boost/lexical_cast.hpp>	// for number convertion.


// computational accuracy definition
#ifdef COMPUTATIONAL_ACC_DOUBLE		// the computational accuracy is double.
	typedef double catype;
#else
 #ifdef COMPUTATIONAL_ACC_FLOAT		// the computational accuracy is float.
	typedef float catype;
 #else
  #error "no computational accuracy specified."	// no computational accuracy have defined.
 #endif
#endif	


// main namespace
namespace Simu
{
	
	//////////////////////////////
	// define basic classes
	//////////////////////////////

	// 前向声明Speed
	class Speed;

	// define the class of speed
	class Position
	{
	public:	
		Position();	// 无参构造，默认位置的两个分量均为零
		Position(catype posX, catype posY);	// 构造位置

		std::string CurrentPosition() const;	// 用于输出位置信息
		bool operator==(const Position& pos) const;	// 判断位置是否相同
		catype Distance(const Position& pos) const;	// 计算两点间的距离
		void UpdatePosition(const Speed& speed, const catype second);	// 更新位置坐标

	public:
		catype m_PosX_;	// 当前位置的X坐标
		catype m_PosY_;	// 当前位置的Y坐标
	};	// class Postion


	// define the class of postion
	class Speed
	{
	public:
		Speed();	// 无参构造，默认速度的两个分量均为零
		Speed(catype speedX, catype speedY);	// 构造速度
		
		std::string CurrentSpeed() const;	// 用于输出速度大小
		catype Magnitude() const;		// 计算速度的大小

	public:
		catype m_SpeedX_;	// 当前速度的X轴分量 
		catype m_SpeedY_;	// 当前素的的Y轴分量
	};	// class Speed

}	// namespace Simu


#endif	// UTILS_INCLUDED
