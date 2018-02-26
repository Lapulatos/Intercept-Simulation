#include "simulator.h"

namespace Simu
{

	////////////////////////////////////
	// 模拟器的实现
	////////////////////////////////////

	Simulator::Simulator() :
		CommandList()
	{}

	Simulator::Simulator(const Simulator& simulator) :
		CommandList(simulator)
	{}

	void Simulator::AddCommand(Simu::Command* command)
	{
        this->push_back(CommandHolder(command));
	}

	void Simulator::ExecuteCommands()
	{
		if(this->size() > 0)
		{
            // 依次执行命令
            for(auto command : (*this))
                command->Execute();
            
            // 清空命令列表
            this->clear();
		}
	}

}	// namespace Simu
