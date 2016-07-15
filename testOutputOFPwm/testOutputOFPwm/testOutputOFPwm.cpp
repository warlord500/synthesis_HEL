// testOutputOFPwm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "HAL\HAL.hpp"
#include "PWM_exposed.h"
//! this function is not os independent
int main()
{	
    int stop;
	int32_t status;
	void * pwmValues;
    std::cout << "this is a test project for testing synthesis implementation of hal layer.\n";
	std::cout << "succcess init:" << HALInitialize(0) << "\n";
	void* pwmPort = getPort(0);
	void* pwmPort2 = getPort(0);
	std::cout << "allocateChannel"	<<  allocatePWMChannel(pwmPort, &status) << "\n";
	setPWM(pwmPort, 128,&status);
	setPWM(pwmPort2, -128, &status);
    std::cin >> stop;
    return 0;
}

