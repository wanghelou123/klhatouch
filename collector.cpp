#include "co2Sensor.h"
#include "ch2oSensor.h"
#include <iostream>
using namespace std;

int main()
{
# if 0
	int n = 0;
	serial myserial("/dev/ttySAC1", 9600, 8, 'n', 1);
	unsigned char cmd[]={0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
	unsigned char recv_buffer[20];
	unsigned char *p = cmd;
	int value=0;
	while(1) {
		p=cmd;
		n = myserial.serialWrite(p, sizeof(cmd));
		printf("Write %d bytes  to sensor\n", n);
		for(int i=0; i<n; i++){
			printf("%.2x ", p[i]);	
		}
		printf("\n");

		p = recv_buffer;
		n = myserial.serialRead(p);
		printf("receive %d bytes\n", n);

		for(int i=0; i<n; i++) {
			printf("%.2x ", recv_buffer[i]);	
		}
		printf("\n");

		value = recv_buffer[2]*256 + recv_buffer[3];
		printf("vlaue = %d\n", value);
		::sleep(1);
	}
#endif
	//co2Sensor myco2Sensor;
	ch2oSensor mych2oSensor;
	while(1) {
		//printf("co2 is %d ppm\n", myco2Sensor.getData());
		printf("ch2o is %d ppb\n", mych2oSensor.getData());
		::sleep(1);
	}

	return 0;
}
