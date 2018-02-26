#ifndef MILIOBJ_INCLUDED
#define MILIOBJ_INCLUDED

#include "utils.h"

namespace Simu
{
	//////////////////////////////
	// 定义基本军事物体
	//////////////////////////////

	// 定义军事物体
	class MilitaryObject
	{
	public:
		MilitaryObject();
		MilitaryObject(const MilitaryObject& obj);
		MilitaryObject(const std::string& name, const std::string& discription, const unsigned number);
	
		std::string GetObjectName() const;
		std::string GetObjectDiscription() const;
		unsigned GetObjectNumber() const;

		void SetObjectName(const std::string& name);
		void SetObjectDiscription(const std::string& discription);
		void SetObjectNumber(const unsigned number);
	
		// 时间更新
		virtual void TimeUpdate() = 0;
		
		// 状态记录
		virtual void StatusRecord() = 0;
	protected:
		std::string m_Name_;		// 军事物体的名字
		std::string m_Discription_;	// 军事物体的详细描述
		unsigned m_Number_;		// 军事物体的编号
	};	// class MilitaryObject


	// 定义移动物体
	class MovingObject
	{
	public:
		MovingObject();
		MovingObject(const MovingObject& obj);
		MovingObject(const Simu::Position& pos, const Simu::Speed& speed);

		void SetObjectSpeed(const Simu::Speed& speed);
		void SetObjectPosition(const Simu::Position& pos);
	
		Simu::Speed GetObjectSpeed() const;
		Simu::Position GetObjectPosition() const;

	protected:
		Simu::Speed m_Speed_;		// 军事物体的速度
		Simu::Position m_Position_;	// 军事物体的位置
	};	// class MovingObject


}	// namespace Simu

#endif	// MILIOBJ_INCLUDED

