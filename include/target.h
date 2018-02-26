#ifndef TARGET_INCLUDED
#define TARGET_INCLUDED

#include "miliobj.h"
#include "defence.h"

namespace Simu
{

	////////////////////////////////////
	// 军事目标
	////////////////////////////////////

	// 前向声明军事目标
	class Target;
        typedef std::shared_ptr<Simu::Target> TargetHolder;     // 自动释放实例资源
        typedef std::vector<Simu::Target*> TargetList;            // 守方指针列表[提高程序运行效率]
        typedef std::vector<Simu::TargetHolder> TargetHolderList; // 守方实例列表
	
        // 前向声明守方
        class DefenceObject;
        typedef std::shared_ptr<Simu::DefenceObject> DefenceObjectHolder;       // 持有实例，自动释放实例资源
        typedef std::vector<Simu::DefenceObject*> DefenceObjectList;              // 守方实例指针表[提高程序运行效率]
        typedef std::vector<Simu::DefenceObjectHolder> DefenceObjectHolderList;   // 守方实例表[保存具体实例]


	typedef enum
	{	
		TARGET_UNDAMAGED,	// 未受攻击
		TARGET_DESTROYED	// 遭到破坏
	} TargetStatus;		// 军事目标的状态

	// the definition of target
	class Target : public Simu::MilitaryObject, public Simu::MovingObject
	{
	public:
		Target();
		Target(const Target& target);
		Target(const unsigned number, const Simu::Position& pos, 
		       const TargetStatus status);

		void SetObjectStatus(const TargetStatus status);
		void SetObjectProtectedBy(const Simu::DefenceObjectList& plist);
		TargetStatus GetObjectStatus() const;
		Simu::DefenceObjectList& GetObjectProtectedBy();

		// 时间更新
		void TimeUpdate();

		// 状态记录
		void StatusRecord();

		// 状态更新
		void ChangeStatusDestroyed();
	protected:
		TargetStatus m_Status_;			// 军事目标的状态 
		Simu::DefenceObjectList m_ProtectedBy_;	// 保护该军事目标的守方列表
	};	// class Target

}	// namespace Simu

#endif	// TARGET_INCLUDED
