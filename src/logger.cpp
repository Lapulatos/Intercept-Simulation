#include "logger.h"

#include <fstream>

namespace Simu
{

	/////////////////////////////////
	// 记录器的实现
	/////////////////////////////////

	Logger::Logger(const std::string& filename) :
		std::list<std::string>(), m_FileName_(filename)
	{}

	Logger::~Logger()
	{
		// 创建文件输出流
		std::ofstream ofs(m_FileName_, std::ofstream::out);
		
		// 记录文件打开成功
		if(ofs.is_open())
		{
			// 遍历记录列表
			for(auto str : (*this))
				ofs << str << std::endl;
		
			// 关闭文件输出流
			ofs.close();
		}
		else
		{
			std::cerr << "记录文件 '" << m_FileName_ << "' 打开失败!" << std::endl;
		}
	}

}	// namespace Simu
