#ifndef LOGGER_INCLUDED
#define LOGGER_INCLUDED

#include "utils.h"

namespace Simu
{

	/////////////////////////////////////////
	// 记录器的定义
	/////////////////////////////////////////

	class Logger : public std::list<std::string>
	{
	public:
		Logger(const std::string& filename);
		~Logger();
	protected:
		std::string m_FileName_;	// 保存的文件名	
	};	// class Logger
	

}	// namespace Simu

#endif	// LOGGER_INCLUDED
