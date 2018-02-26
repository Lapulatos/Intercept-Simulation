#include "miliobj.h"

namespace Simu
{

	// the implementation of MilitaryObject
	MilitaryObject::MilitaryObject() :
		m_Name_(""), m_Discription_(""), m_Number_(0)
	{}

	MilitaryObject::MilitaryObject(const MilitaryObject& obj) :
		m_Name_(obj.m_Name_), m_Discription_(obj.m_Discription_), m_Number_(obj.m_Number_)
	{}

	MilitaryObject::MilitaryObject(const std::string& name, const std::string& discription, const unsigned number) :
		m_Name_(name), m_Discription_(discription), m_Number_(number)
	{}
	
	std::string MilitaryObject::GetObjectName() const
	{
		return m_Name_;
	}

	std::string MilitaryObject::GetObjectDiscription() const
	{
		return m_Discription_;
	}

	unsigned MilitaryObject::GetObjectNumber() const
	{
		return m_Number_;
	}

	void MilitaryObject::SetObjectName(const std::string& name)
	{
		m_Name_ = name;
	}

	void MilitaryObject::SetObjectDiscription(const std::string& discription)
	{
		m_Discription_ = discription;
	}

	void MilitaryObject::SetObjectNumber(const unsigned number)
	{
		m_Number_ = number;
	}


	// the implementation of MovingObject
	MovingObject::MovingObject() :
		m_Position_(0.0f, 0.0f), m_Speed_(0.0f, 0.0f)
	{}

	MovingObject::MovingObject(const MovingObject& obj) :
		m_Position_(obj.m_Position_), m_Speed_(obj.m_Speed_)
	{}

	MovingObject::MovingObject(const Simu::Position& pos, const Simu::Speed& speed) :
		m_Position_(pos), m_Speed_(speed)
	{}

	void MovingObject::SetObjectSpeed(const Simu::Speed& speed)
	{
		m_Speed_ = speed;
	}

	void MovingObject::SetObjectPosition(const Simu::Position& pos)
	{
		m_Position_ = pos;
	}

	Simu::Speed MovingObject::GetObjectSpeed() const
	{
		return m_Speed_;
	}

	Simu::Position MovingObject::GetObjectPosition() const
	{
		return m_Position_;
	}
	

}	// class Simu

