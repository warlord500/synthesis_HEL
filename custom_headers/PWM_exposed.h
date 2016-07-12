#include "general.h"
/*! @file PWM_exposed.h

  this file exposes the inner details of 
  the pwm implementation so that the packet server
  can quickly send data to the unity server.
*/
//! get the raw buffer to the pwm values.
int32_t* getPWMVAlues(void* pwmGenerator);
//! length of buffer from <getPWMValues>
int32_t* getPWMLength(void* pwmGenerator);
