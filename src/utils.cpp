#include "utils.h"

namespace Simu
{

	/////////////////////////////////////
	// the implements of Position
	/////////////////////////////////////

	Position::Position() :
		m_PosX_((catype)0.0f), m_PosY_((catype)0.0f)
	{}

	Position::Position(catype posX, catype posY) :
		m_PosX_(posX), m_PosY_(posY)
	{}

	std::string Position::CurrentPosition() const
	{
		// 输出格式"(x, y)"
		std::string str = "(" + boost::lexical_cast<std::string>(m_PosX_) + ", " +
					boost::lexical_cast<std::string>(m_PosY_) + ")";
		return str;
	}

	bool Position::operator==(const Position& pos) const
	{
		// 当两个位置的分量对应相等时，返回为真
		if((m_PosX_ == pos.m_PosX_) && (m_PosY_ == pos.m_PosY_))
			return true;
		return false;
	}

	catype Position::Distance(const Position& pos) const
	{
		catype result = (catype)0.0f;

		// 计算坐标之差
		catype diffX = m_PosX_ - pos.m_PosX_;
		catype diffY = m_PosY_ - pos.m_PosY_;
		
		// 计算两个位置之间的距离
		result = (catype)std::sqrt(diffX*diffX + diffY*diffY);

		return result;
	}

	void Position::UpdatePosition(const Speed& speed, const catype second)
	{
		m_PosX_ += speed.m_SpeedX_ * second;
		m_PosY_ += speed.m_SpeedY_ * second;
	}

	
	/////////////////////////////////////
	// the implements of Speed
	/////////////////////////////////////

	Speed::Speed() :
		m_SpeedX_((catype)0.0f), m_SpeedY_((catype)0.0f)
	{}

	Speed::Speed(catype speedX, catype speedY) :
		m_SpeedX_(speedX), m_SpeedY_(speedY)
	{}

	std::string Speed::CurrentSpeed() const
	{
		// 输出格式"(vx, vy)"
		std::string str = "(" + boost::lexical_cast<std::string>(m_SpeedX_) + ", " +
					boost::lexical_cast<std::string>(m_SpeedY_) + ")";
		return str;
	}

	catype Speed::Magnitude() const
	{
		catype result = (catype)0.0f;

		// 计算速度的大小
		result = (catype)std::sqrt(m_SpeedX_*m_SpeedX_ + m_SpeedY_*m_SpeedY_);

		return result;
	}
}

