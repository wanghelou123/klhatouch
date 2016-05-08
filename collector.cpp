#include "co2Sensor.h"
#include "ch2oSensor.h"
#include "pm2_5Sensor.h"
#include "sht11.h"
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
	//ch2oSensor mych2oSensor;

	//pm2_5Sensor _pm2_5Sensor;
	sht11 _sht11;
	while(1) {
		//printf("co2 is %d ppm\n", myco2Sensor.getData());
		//printf("ch2o is %d ppb\n", mych2oSensor.getData());
		//_pm2_5Sensor.getData();
		//printf("std pm1.0 is %d\n", _pm2_5Sensor.getStdpm1_0());
		//printf("std pm2.5 is %d\n", _pm2_5Sensor.getStdpm2_5());
		//printf("std pm10 is %d\n", _pm2_5Sensor.getStdpm10());
		//printf("air pm1.0 is %d\n", _pm2_5Sensor.getAirpm1_0());
		//printf("air pm2.5 is %d\n", _pm2_5Sensor.getAirpm2_5());
		//printf("air pm10 is %d\n", _pm2_5Sensor.getAirpm10());

		printf("temperature: <%.2f> °C\n", float(_sht11.get_temperature())/1000);
		printf("humidity: <%.2f> %RH\n", float(_sht11.get_humidity())/1000);
		::sleep(1);
	}

	return 0;
}
