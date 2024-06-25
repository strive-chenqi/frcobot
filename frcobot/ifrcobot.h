#pragma once
#include "network_interface.h"
#include "robot.h"

class ManualMode; // 前向声明
class AutoMode;   // 前向声明
class IFrcoBot;

//状态模式是每一个子类实现一个与Context(IRobotMode)的一个状态相关的行为，也可以稍加更改，每个子类实现同一种方法，但实现方式不一样
class IRobotMode {
public:
	virtual ~IRobotMode() = default;
	virtual void specificOperation() = 0; // 具体操作方法
	virtual void init(IFrcoBot* ifcrbot) = 0; // 初始化方法
};


//template<typename T>
class IFrcoBot
{
	friend class ManualMode; //声明为友元类方便访问robot_等
	friend class AutoMode;

public:
	//static T& GetInstance() {
	//	static T instance; 
	//	
	//	return instance;
	//}
	
	//单例模式与状态模式结合
	static IFrcoBot& GetInstance(IRobotMode* mode) {
		static IFrcoBot instance;

		instance.setMode(mode);  

		return instance;
	}


private:
	IFrcoBot() : current_mode_(nullptr) {};
	virtual ~IFrcoBot();

	void setMode(IRobotMode* mode);
	int connectRobot();

//protected:
//	IFrcoBot() : current_mode_(nullptr){};
//	virtual ~IFrcoBot();

	

private:
	FRRobot robot_;                    //实例化机器人对象

	IRobotMode* current_mode_; // 当前模式

};