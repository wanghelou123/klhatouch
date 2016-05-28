#ifndef CO2SENSOR_H
#define CO2SENSOR_H

#include "serial.h"

class co2Sensor {
	public:
		co2Sensor();
		~co2Sensor();
		int getData();
	private:
		unsigned char cmd[9];
		unsigned char recv_buffer[512];
		serial * myserial;
};
#endif
