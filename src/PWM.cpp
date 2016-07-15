#include "HAL/Digital.hpp"
#include "general.h"
#include "HAL/cpp/Resource.hpp"
#include "stdio.h"
#include "PWM_exposed.h"
#include "HAL\Errors.hpp"
#include <mutex>
#include <array>

static hal::Resource* pwmChannels = nullptr;
std::array<unsigned short, kPwmPins> pwmChannelValues;
std::mutex lockerPWMValues;
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
		 *status = 0; //successful operation no error
		 int work = pwmChannels->Allocate(pwmChannelNum, "pwmChannel");
		 if (work == ~0ul) *status == RESOURCE_IS_ALLOCATED;
		 return (work == ~0ul);
	 }
	void freePWMChannel(void* digital_port_pointer, int32_t *status)
	 {
		 uint32_t pwmChannelNum = ((uint32_t)digital_port_pointer - (uint32_t)&pwmChannelValues)
			 / sizeof(pwmChannelValues[0]);
		 pwmChannels->Free(pwmChannelNum);
		 *status == 0;
		//currently no way to  send out errors
	 }
	/*!
		get the pwm that was set using setpwm
		@param ret value of getPort() 
		@param errors capable of getting
	*/
	unsigned short getPWM(void* digital_port_pointer, int32_t *status) 
	{
		
		if (checkPWMChannel(digital_port_pointer)) 
		{
			std::lock_guard<std::mutex> lock (lockerPWMValues);
			auto* valueptr = static_cast<unsigned short*>(digital_port_pointer); 
			return *valueptr; //value is in pwmChannelValues array
		} 
		else 
		{
			*status == NULL_PARAMETER;
			return 0;
		}
	}
	/*!
	@brief	set port to value

	set value into in pwmChannelValues

	@param ret value of getPort()
	@param errors capable of getting
	*/
	void setPWM(void* digital_port_pointer, unsigned short value, int32_t *status)
	{
		if (checkPWMChannel(digital_port_pointer))
		{
			//make sure no one is trying to read the data at the same time.
			std::lock_guard<std::mutex>lock(lockerPWMValues);
			auto* valueptr = static_cast<unsigned short*>(digital_port_pointer);
			*valueptr == value; //value is set in pwmChannelValues array
		}
		else {
			*status == NULL_PARAMETER;
		}
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
