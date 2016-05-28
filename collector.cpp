#include "co2Sensor.h"
#include "ch2oSensor.h"
#include "pm2_5Sensor.h"
#include "sht11.h"
#include "htu21d.h"
#include "shmMem.h"
#include <iostream>
using namespace std;
#define HTU21D
#define CO2
#define CH2O
#define PM2_5
#define MS5611

int main()
{
	//共享内存
	shmMem myshm;
	//温湿度传感器
	htu21d myhtu21d;
	//二氧化碳
	co2Sensor myco2Sensor;
	//甲醛
	ch2oSensor mych2oSensor;
	//pm2.5 pm10
	pm2_5Sensor _pm2_5Sensor;

	//sht11 _sht11;
	while(1) {
#if 1
		//温度
		myshm.setval(0, myhtu21d.get_temperature());
		//湿度
		myshm.setval(1, myhtu21d.get_humidity());
		//二氧化碳
		myshm.setval(2, myco2Sensor.getData());
		//大气压力
		//myshm.setval(3, myco2Sensor.getData());
		//甲醛 ch2o
		myshm.setval(4, mych2oSensor.getData());

		_pm2_5Sensor.getData();
		//pm1.0
		myshm.setval(5, _pm2_5Sensor.getStdpm1_0());
		//pm2.5
		myshm.setval(6, _pm2_5Sensor.getStdpm2_5());
		//pm10
		myshm.setval(7, _pm2_5Sensor.getStdpm10());
	#endif
#ifdef HTU21D
		printf("temperature: %d\n", myhtu21d.get_temperature());
		printf("humidity: %d\n", myhtu21d.get_humidity());
#endif

#ifdef CO2
		printf("co2 is %d ppm\n", myco2Sensor.getData());

#endif
#ifdef CH2O
		printf("ch2o is %d ppb\n", mych2oSensor.getData());
#endif
#ifdef PM2_5
		_pm2_5Sensor.getData();
		printf("std pm1.0 is %d\n", _pm2_5Sensor.getStdpm1_0());
		printf("std pm2.5 is %d\n", _pm2_5Sensor.getStdpm2_5());
		printf("std pm10 is %d\n", _pm2_5Sensor.getStdpm10());
#endif

		//printf("air pm1.0 is %d\n", _pm2_5Sensor.getAirpm1_0());
		//printf("air pm2.5 is %d\n", _pm2_5Sensor.getAirpm2_5());
		//printf("air pm10 is %d\n", _pm2_5Sensor.getAirpm10());
		::sleep(5);
	}

	return 0;
}
