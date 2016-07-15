// testOutputOFPwm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "HAL\HAL.h"
#include "PWM_exposed.h"
//! this function is not os independent
int main()
{	
    int stop;
	void * pwmValues;
    std::cout << "this is a test project for testing synthesis implementation of hal layer.\n";
	std::cout << "succcess init:" << HALInitialize(0) << "\n";
	pwmValues = &pwmChannelValues;
	std::cout << "is correct digital port" << checkPWMChannel(pwmValues) << "\n";

    std::cin >> stop;
    return 0;
}

