// testOutputOFPwm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HAL\Digital.hpp"
#include <iostream>

int main()
{	
	int stop;
	std::cout << "this is a test project for testing my implementation of hal layer.";
	std::cout << allocatePWMChannel(nullptr, nullptr);
	std::cin >> stop;
	return 0;
}

