#ifndef	__SHMMEM__H
#define	__SHMMEM__H
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <sys/stat.h>
//#include "commApp.h"
#define SHM_NUM		(27*4)//27*4
#define IFLAGS 		(IPC_CREAT)
#define SHMKEY		ftok("/etc/passwd", 'b')

//数据在共享内存中的地址
#define	ANALOG_INPUT_START		0
#define	ANALOG_INPUT_END		7
#define	DS18B20					8
#define	IIC_TEMPERATURE			9
#define	PWM_INPUT_START			10
#define	PWM_INP_END				13
#define	RELAY_CTL_START			14
#define	RELAY_CTL_END			20
#define	BEEP					21
#define	ANALOG_OUTPUT_START		22
#define	ANALOG_OUTPUT_END		25
#define	PWM_OUTPUT				26



#define	RELAY_START	
class shmMem{
public:
	shmMem();
	~shmMem();
	int getval(int channel);
	int setval(int channel, int val);
private:
	int		shmid;
	int		*shmptr;
};
#endif
