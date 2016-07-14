#include "HAL\HAL.hpp"
#include "general.h"
#include "stdio.h"
#include "StateNetworkServer.h"
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
		 if (emulatorThread != nullptr)
		 {
			 return 0; //emulator has been initilized successfully.
		 } else 
		 {
			 return -1;
		 }


	
	}

	



}