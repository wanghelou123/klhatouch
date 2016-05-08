#include <stdio.h>
#include <stdlib.h>
#include "sht11.h"
sht11::sht11()
{
}
sht11::~sht11()
{
}
int sht11::get_temperature()
{
	char buffer[20];
	FILE *fp = fopen("/sys/devices/platform/sht11/temp1_input", "r");
	if(!fp) {
		perror("fopen");	
		return 0;
	}
	fgets(buffer, sizeof(buffer), fp);
	fclose(fp);
	
	return atoi(buffer);
}
int sht11::get_humidity()
{
	char buffer[20];
	FILE *fp = fopen("/sys/devices/platform/sht11/humidity1_input", "r");
	if(!fp) {
		perror("fopen");	
		return 0;
	}
	fgets(buffer, sizeof(buffer), fp);
	fclose(fp);
	
	return atoi(buffer);
}
