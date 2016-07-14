#include "HAL/Port.h"'
#pragma once
/*! @file PWM_exposed.h

  this file exposes the inner details of 
  the pwm implementation so that the packet server
  can quickly send data to the unity server.
*/
//! get the raw buffer to the pwm values.
int32_t* getPWMVAlues(void* pwmGenerator);
//! length of buffer from <getPWMValues>
int32_t* getPWMLength(void* pwmGenerator);
bool intializePWM();

//! this number is pulled from Digital.cpp
const uint32_t kPwmPins = 20;
extern float pwmChannelValues[kPwmPins];
struct DigitalPort {
	Port port;
	uint32_t PWMGeneratorID;
};
