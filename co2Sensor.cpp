#include "co2Sensor.h"
#include <stdio.h>
#include <string.h>

co2Sensor::co2Sensor()
{
	myserial = new serial("/dev/ttyO1", 9600, 8, 'n', 1);
}

co2Sensor::~co2Sensor()
{
	delete myserial;
}

int co2Sensor::getData()
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
		unsigned char *p=cmd;
		int n = myserial->serialWrite(p, sizeof(cmd));
	#if 0
		printf("Write %d bytes  to sensor\n", n);
		for(int i=0; i<n; i++){
			printf("%.2x ", p[i]);	
		}
		printf("\n");
	#endif

		memset(recv_buffer, 0, sizeof(recv_buffer));
		p = recv_buffer;
		n = myserial->serialRead(p);
	#if 0
		printf("receive %d bytes\n", n);

		for(int i=0; i<n; i++) {
			printf("%.2x ", recv_buffer[i]);	
		}
		printf("\n");
	#endif

		//计算ppm值
		int value = (recv_buffer[2]<<8) + recv_buffer[3];

		return value;
}
