#include "ifrcobot.h"

int IFrcoBot::connectRobot()
{   
    return robot_.RPC("192.168.58.2"); //与机器人控制器建立通信连接
}

IFrcoBot::~IFrcoBot()
{
}

void IFrcoBot::setMode(IRobotMode* mode)
{
	current_mode_ = mode;
	if (current_mode_) {
		current_mode_->init(this); // 调用对应模式的初始化方法
	}
}
