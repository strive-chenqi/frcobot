#include "network_interface.h"
#include <stdio.h>
#include <exception>
#include <iostream>

using namespace std;

int main(void)
{
	
    NetworkInterface test;

	//test.init();

	test.eventListen();

	test.eventLoop();
	
	
}