#include "network_interface.h"
#include "frcobot.h"
#include <stdio.h>
#include <exception>
#include <iostream>

using namespace std;

int main(void)
{
	
    // 获取机器人实例
    IFrcoBot& robot = IFrcoBot::GetInstance(new ManualMode);
    


	
    return 0;
	
}