#include "pm2_5Sensor.h"
#include <stdio.h>
#include <string.h>

pm2_5Sensor::pm2_5Sensor()
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

pm2_5Sensor::~pm2_5Sensor()
{
	delete myserial;
}

int pm2_5Sensor::getData()
{
#if 0
	unsigned char *p=cmd;
	int n = myserial->serialWrite(p, sizeof(cmd));
	printf("Write %d bytes  to sensor\n", n);
	for(int i=0; i<n; i++){
		printf("%.2x ", p[i]);	
	}
	printf("\n");

	memset(recv_buffer, 0, sizeof(recv_buffer));
#endif
	unsigned char *p = recv_buffer;
	int n = myserial->serialRead(p);
	printf("receive %d bytes\n", n);

	for(int i=0; i<n; i++) {
		printf("%.2x ", recv_buffer[i]);	
	}
	printf("\n");

	//计算ppm值
	int value = (recv_buffer[2]<<8) + recv_buffer[3];

	return value;
}

int pm2_5Sensor::getStdpm1_0()
{
	//pm1.0
	int value = (recv_buffer[4]<<8) + recv_buffer[5];

	return value;
}

int pm2_5Sensor::getStdpm2_5()
{
	//pm2.5
	int value = (recv_buffer[6]<<8) + recv_buffer[7];

	return value;
}

int pm2_5Sensor::getStdpm10()
{
	//pm10
	int value = (recv_buffer[8]<<8) + recv_buffer[9];

	return value;
}

int pm2_5Sensor::getAirpm1_0()
{
	//pm1.0
	int value = (recv_buffer[10]<<8) + recv_buffer[11];

	return value;
}

int pm2_5Sensor::getAirpm2_5()
{
	//pm2.5
	int value = (recv_buffer[12]<<8) + recv_buffer[13];

	return value;
}

int pm2_5Sensor::getAirpm10()
{
	//pm10
	int value = (recv_buffer[14]<<8) + recv_buffer[15];

	return value;
}
