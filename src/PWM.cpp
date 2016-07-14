#include "HAL/Digital.hpp"
#include "general.h"
#include "HAL\cpp\Resource.hpp"
#include "stdio.h"
#include "PWM_exposed.h"


static bool verifyPWMChannel(DigitalPort *port, int32_t *status);
static hal::Resource* pwmChannels = nullptr;
float pwmChannelValues[kPwmPins];


extern "C" {
	bool checkPWMChannel(void* digital_port_pointer) {
		bool retvalue = ((uint32_t)digital_port_pointer - (uint32_t)&pwmChannelValues) / sizeof(float) < kPwmPins;
		retvalue &= digital_port_pointer > &pwmChannelValues;
	}

	void setPWM(void* digital_port_pointer, unsigned short value, int32_t *status){}

	 bool allocatePWMChannel(void* digital_port_pointer, int32_t *status) 
	 {
		 return true;
	 }
	
}
/////////////////////////////////////////////////////////////////////////////////////////
//below is code for pwm_exposed.
/////////////////////////////////////////////////////////////////////////////////////////
static bool verifyPWMChannel(DigitalPort *port, int32_t *status) {
	if (port == NULL) {
		*status = NULL_PARAMETER;
		return false;
	}
	else if (!checkPWMChannel(port)) {
		*status = PARAMETER_OUT_OF_RANGE;
		return false;
	}
	else {
		return true;
	}
}
bool intializePWM() 
{
	//18 is default value for channels.
	hal::Resource::CreateResourceObject(&pwmChannels, kPwmPins);
	//the function sets pointer when it is completed.
	printf("create allocator object.");
	return pwmChannels != nullptr;
}