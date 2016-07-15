#include "HAL\HAL.hpp"
#include "general.h"
#include "stdio.h"
#include "StateNetworkServer.h"
#include "custom_headers\PWM_exposed.h"
#include <algorithm>
#include <iterator>

static DWORD WINAPI emulator(LPVOID nonExistData) // THIS VERSION IS ONLY FOR WINAPI ONLY 
{
	printf("executing emulator packet code");
	StateNetworkServer server;
	OutputStatePacket outPack;
	server.Open();
	while (true) {
		std::array<unsigned short, kPwmPins> pwmCopy;
		{//keep scope for lock guard to release mutex
			std::lock_guard<std::mutex> lock(lockerPWMValues);
			std::copy(pwmChannelValues.begin(), pwmChannelValues.end(), pwmCopy.begin());
		}
		for (int i = 0; i < kPwmPins; i++) 
		{
			outPack.dio[0].pwmValues[i] =  (float)pwmCopy[i];
		}
		server.SendStatePacket(outPack);
		Sleep(50);
	}
	server.Close();
	return 0;
}
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
		return getPortWithModule(pin, 1);//pwm ports
	}
	void* getPortWithModule(uint8_t module, uint8_t pin)
	{
		if (module == 1)
		{
			return &pwmChannelValues[pin];
		}
		return nullptr;//no module to be used.
	}
	void freePort(void* digital_port_pointer) {return;} //nothing allocated so nothing to free
	

}