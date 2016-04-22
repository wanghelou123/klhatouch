#ifndef CH2OSENSOR_H
#define CH2OSENSOR_H

#include "serial.h"

class ch2oSensor {
	public:
		ch2oSensor();
		~ch2oSensor();
		int getData();
	private:
		unsigned char cmd[9];
		unsigned char recv_buffer[9];
		serial * myserial;
};
#endif
