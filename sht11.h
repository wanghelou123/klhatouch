#ifndef SHT11_H
#define SHT11_H
class sht11 {
public:
	sht11();
	~sht11();
	int get_temperature();
	int get_humidity();
};
#endif
