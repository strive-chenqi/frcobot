#include "ifrcobot.h"

int IFrcoBot::connectRobot()
{   
    return robot_.RPC("192.168.58.2"); //������˿���������ͨ������
}

IFrcoBot::~IFrcoBot()
{
}

void IFrcoBot::setMode(IRobotMode* mode)
{
	current_mode_ = mode;
	if (current_mode_) {
		current_mode_->init(this); // ���ö�Ӧģʽ�ĳ�ʼ������
	}
}
