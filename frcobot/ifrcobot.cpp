#include "ifrcobot.h"

int IFrcoBot::connectRobot()
{
    FRRobot robot;                    //ʵ���������˶���
    return robot.RPC("192.168.58.2"); //������˿���������ͨ������
}
