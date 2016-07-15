#include "HAL\HAL.hpp"
#include "general.h"
#include "stdio.h"
#include "StateNetworkServer.h"
#include "custom_headers\PWM_exposed.h"
#include "custom_headers\PWM_exposed.h"
static DWORD WINAPI emulator(LPVOID nonExistData) // THIS VERSION IS ONLY FOR WINAPI ONLY 
{
	printf("executing emulator packet code");
	StateNetworkServer server;
	OutputStatePacket outPack;
	server.Open();
	while (true) {
		outPack.dio[0].pwmValues[0] = 0.75f;
		outPack.dio[0].pwmValues[1] = -0.75f;
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
	void* getPort(int pin) 
	{
		getPortWithModule(pin, 1);//pwm ports
	}
	void* getPortWithModule(int pin, int module) 
	{
		if (module == 1)
		{
			return &pwmChannelValues[pin];
		}
		return nullptr;//no module to be used.
	}
	void freePort(void* digital_port_pointer) {return;} //nothing allocated so nothing to free

}