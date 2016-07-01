#include "HAL\Power.hpp"
extern "C"
{
	float getVinVoltage(int32_t *status) 
	{ 
		return 12.1f; 
	}
	float getVinCurrent(int32_t *status)
	{ 
		return 0.0f; 
	}
	float getUserVoltage6V(int32_t *status)
	{ 
		return 0.0f; 
	}
	float getUserCurrent6V(int32_t *status) 
	{ 
		return 0.0f; 
	}
	bool getUserActive6V(int32_t *status) 
	{ 
		return true; 
	}
	int getUserCurrentFaults6V(int32_t *status) 
	{ 
		return 0; 
	}
	float getUserVoltage5V(int32_t *status)
	{ 
		return 0.0f; 
	}
	float getUserCurrent5V(int32_t *status)
	{ 
		return 0.0f; 
	}
	bool getUserActive5V(int32_t *status) 
	{ 
		return false; 
	}
	int getUserCurrentFaults5V(int32_t *status) 
	{ 
		return 0; 
	}
	float getUserVoltage3V3(int32_t *status)
	{ 
		return 0.0f; 
	}
	float getUserCurrent3V3(int32_t *status)
	{ 
		return 0.0f; 
	}
	bool getUserActive3V3(int32_t *status) 
	{ 
		return false; 
	}
	int getUserCurrentFaults3V3(int32_t *status) 
	{ 
		return 0; 
	}
}
