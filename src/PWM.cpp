#include "HAL/Digital.hpp"
#include "general.h"
#include "HAL\cpp\Resource.hpp"
#include "stdio.h"

static hal::Resource* pwmChannelAllocator = nullptr;
extern "C" {
	void setPWM(void* digital_port_pointer, unsigned short value, int32_t *status){}
	 bool allocatePWMChannel(void* digital_port_pointer, int32_t *status) { return  false; }
	void freePWMChannel(void* digital_port_pointer, int32_t *status){}
 unsigned short getPWM(void* digital_port_pointer, 
         int32_t *status)
    {
        return 0;
    }
	void latchPWMZero(void* digital_port_pointer, int32_t *status){}
	void setPWMPeriodScale(void* digital_port_pointer, uint32_t squelchMask, int32_t *status){}
	void* allocatePWM(int32_t *status) { 
		return nullptr;
	}
	void freePWM(void* pwmGenerator, int32_t *status){}
	void setPWMRate(double rate, int32_t *status){}
	void setPWMDutyCycle(void* pwmGenerator, double dutyCycle, int32_t *status){}
	void setPWMOutputChannel(void* pwmGenerator, uint32_t pin, int32_t *status){}
}
bool intializePWM() 
{
	// the number 18 comes from the digitalINternal file.
	hal::Resource::CreateResourceObject(&pwmChannelAllocator, 18);
	//the function sets pointer when it is completed.
	printf("create allocator object.");
	return pwmChannelAllocator != nullptr;
}