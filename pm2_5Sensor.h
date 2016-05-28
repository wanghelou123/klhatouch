#ifndef PM2_5SENSOR_H 
#define PM2_5SENSOR_H 

#include "serial.h"

class pm2_5Sensor{
	public:
		pm2_5Sensor();
		~pm2_5Sensor();
		int getData();
		int getStdpm1_0();
		int getStdpm2_5();
		int getStdpm10();
		int getAirpm1_0();
		int getAirpm2_5();
		int getAirpm10();
	private:
		unsigned char cmd[9];
		unsigned char recv_buffer[256];
		serial * myserial;
};
#endif
