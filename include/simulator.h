#ifndef SIMULATOR_INCLUDED
#define SIMULATOR_INCLUDED

#include "utils.h"
#include "command.h"

namespace Simu
{

	///////////////////////////////////////////
	// 模拟器的定义
	///////////////////////////////////////////

	// for convenient
	typedef std::list<Simu::CommandHolder> CommandList;

    class Simulator : public CommandList
	{
	public:
		Simulator();
		Simulator(const Simulator& simulator);	

		void AddCommand(Simu::Command* command);	// 设置命令
		void ExecuteCommands(); 	// 模拟器执行所有命令

    };	// class Simulator

}	// namespace Simu


#endif	// SIMULATOR_INCLUDED
