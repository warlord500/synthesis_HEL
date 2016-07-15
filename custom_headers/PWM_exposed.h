#pragma once
/*! @file PWM_exposed.h

  this file exposes the inner details of 
  the pwm implementation so that the packet server
  can quickly send data to the unity server.
*/
bool intializePWM();

//! this number is pulled from Digital.cpp
const uint32_t kPwmPins = 20;
extern float pwmChannelValues[kPwmPins];