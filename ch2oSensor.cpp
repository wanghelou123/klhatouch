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
	myserial = new serial("/dev/ttySAC1", 9600, 8, 'n', 1);
}

ch2oSensor::~ch2oSensor()
{
	delete myserial;
}

int ch2oSensor::getData()
{
		unsigned char *p=cmd;
#if 0
		int n = myserial->serialWrite(p, sizeof(cmd));
		printf("Write %d bytes  to sensor\n", n);
		for(int i=0; i<n; i++){
			printf("%.2x ", p[i]);	
		}
		printf("\n");
#endif
		memset(recv_buffer, 0, sizeof(recv_buffer));
		p = recv_buffer;
		int n = myserial->serialRead(p);
		printf("receive %d bytes\n", n);

		for(int i=0; i<n; i++) {
			printf("%.2x ", recv_buffer[i]);	
		}
		printf("\n");

		//计算ppm值
		int value = (recv_buffer[5]<<8) + recv_buffer[6];

		return value;
}
