#include "HAL\HAL.hpp"
#include "general.h"
#include "stdio.h"
extern "C" {
	static DWORD WINAPI emulator(LPVOID nonExistData) // THIS VERSION IS ONLY FOR WINAPI ONLY 
	{
		printf("executing emulator packet code");
	
		return 0;
	}

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
			 return 0; //emulator has been initilized successfully.
	}

	



}