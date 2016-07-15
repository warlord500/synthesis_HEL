#include "HAL/Digital.hpp"
#include "general.h"
#include "HAL/cpp/Resource.hpp"
#include "stdio.h"
#include "PWM_exposed.h"


static bool verifyPWMChannel(DigitalPort *port, int32_t *status);
static hal::Resource* pwmChannels = nullptr;
float pwmChannelValues[kPwmPins];
//converts pointers to uint32_t's
static_assert(sizeof(uint32_t) <= sizeof(void *), "This file shoves uint32_ts into pointers.");


extern "C" {
	bool checkPWMChannel(void* digital_port_pointer) { 
		return digital_port_pointer < (&pwmChannelValues + sizeof(pwmChannelValues))
			&& digital_port_pointer >= &pwmChannelValues;
	}


	 bool allocatePWMChannel(void* digital_port_pointer, int32_t *status) 
	 {
		 uint32_t pwmChannelNum = ((uint32_t)digital_port_pointer - (uint32_t)&pwmChannelValues) 
			 / sizeof(pwmChannelValues[0]);
		 *status == 0; //successful operation no error
		 return pwmChannels->Allocate(pwmChannelNum, "pwmChannel");
	 }
	 bool freePWMChannel(void* digital_port_pointer) 
	 {
		 uint32_t pwmChannelNum = ((uint32_t)digital_port_pointer - (uint32_t)&pwmChannelValues)
			 / sizeof(pwmChannelValues[0]);
		 pwmChannels->Free(pwmChannelNum);
		 return true;
	 }

}
/////////////////////////////////////////////////////////////////////////////////////////
//below is code for pwm_exposed.
/////////////////////////////////////////////////////////////////////////////////////////
bool intializePWM() 
{
	//18 is default value for channels.
	hal::Resource::CreateResourceObject(&pwmChannels, kPwmPins);
	//the function sets pointer when it is completed.
	printf("create allocator object.\n");
	return pwmChannels != nullptr;
}
