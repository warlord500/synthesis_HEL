#include "HAL\HAL.hpp"
#include "general.h"
#include "stdio.h"
#include "StateNetworkServer.h"
#include "custom_headers\PWM_exposed.h"
#include <algorithm>
#include <iterator>

extern "C" {


	int HALInitialize(int mode) {
		bool retvalue; // this is return code info
		//create thread for sending packet information.
		// winapi only
		
		DWORD emulatorThreadid;
		 HANDLE emulatorThread = CreateThread(
				nullptr,                   // default security attributes
				0,                      // use default stack size  
				emulator,       // thread function name
				nullptr,          // argument to thread function 
				0,                      // use default creation flags 
				&emulatorThreadid);   // returns the thread identifier
		 retvalue = (emulatorThread != nullptr);
		 retvalue &= intializePWM();
		 return 0; // return successfully
	}	
	void* getPort(uint8_t pin)
	{
		return getPortWithModule(1,pin);//pwm ports
	}
	void* getPortWithModule(uint8_t module, uint8_t pin)
	{
		if (module == 1)
		{
			return &pwmChannelValues[pin-1];//array 0 index based and pins are 1 based
		}
		return nullptr;//no module to be used.
	}
	void freePort(void* digital_port_pointer) {return;} //nothing allocated on heap so nothing to free
	

}