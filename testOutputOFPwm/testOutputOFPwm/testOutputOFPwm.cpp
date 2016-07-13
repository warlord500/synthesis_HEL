// testOutputOFPwm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HAL\Digital.hpp"
#include <iostream>
#include "general.h"
#include "HAL\HAL.hpp"
//! this function is not os independent
int main()
{	
    int stop;
  
    std::cout << "this is a test project for testing synthesis implementation of hal layer.";
	std::cout << "before hal initilize!";
std::cout << "zero if succcess" << HALInitialize(0) << std::endl;
std::cout << "end of program";

    std::cin >> stop;
    return 0;
}

