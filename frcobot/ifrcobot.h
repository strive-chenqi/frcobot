#pragma once
#include "network_interface.h"
#include "robot.h"

class IFrcoBot
{
public:
	int connectRobot();
	virtual int handautoSwitch() = 0;

protected:


private:
	

};