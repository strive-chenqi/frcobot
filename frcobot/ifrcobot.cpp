#include "ifrcobot.h"

int IFrcoBot::connectRobot()
{
    FRRobot robot;                    //实例化机器人对象
    return robot.RPC("192.168.58.2"); //与机器人控制器建立通信连接
}
