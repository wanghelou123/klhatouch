#include "ch2oSensor.h"
#include <stdio.h>
#include <string.h>

ch2oSensor::ch2oSensor()
{
	cmd[0] = 0xFF;
	cmd[1] = 0x01;
	cmd[2] = 0x86;
	cmd[3] = 0x00;
	cmd[4] = 0x00;
	cmd[5] = 0x00;
	cmd[6] = 0x00;
	cmd[7] = 0x00;
	cmd[8] = 0x79;
	unsigned char require_mode_cmd[]= 
	{0xFF, 0x01, 0x78, 0x40, 0x00, 0x00, 0x00, 0x00, 0x47};
	myserial = new serial("/dev/ttyO2", 9600, 8, 'n', 1);
	
	unsigned char *p = require_mode_cmd;
	myserial->serialWrite(p, sizeof(require_mode_cmd));
	printf("=============change require after active mode.\n");

}

ch2oSensor::~ch2oSensor()
{
	delete myserial;
}

int ch2oSensor::getData()
{
#if 0
		unsigned char *p=cmd;
		int n = myserial->serialWrite(p, sizeof(cmd));
		printf("Write %d bytes  to sensor\n", n);
		for(int i=0; i<n; i++){
			printf("%.2x ", p[i]);	
		}
		printf("\n");
#endif
		memset(recv_buffer, 0, sizeof(recv_buffer));
		unsigned char * p = recv_buffer;
		int n = myserial->serialRead(p);

#if 0
		printf("receive %d bytes\n", n);
		for(int i=0; i<n; i++) {
			printf("%.2x ", recv_buffer[i]);	
		}
		printf("\n");
#endif

		//计算ppm值
		int value = (recv_buffer[5]<<8) + recv_buffer[6];

		return value;
}
