#ifndef __COMMAPP__H
#define __COMMAPP__H

#include "serial.h"
#include "shmMem.h"
#define		TRUE	1
#define		FALSE	0
//#define 	FUNC

/*输入寄存器*/
#define		INPUT_REG_START_ADDR	0x00	
#define		INPUT_REG_END_ADDR		0x07
#define		INPUT_REG_MAX_NUM		(INPUT_REG_END_ADDR+0x01)//7个

/*总寄存器个数*/
#define		REGS_NUM	(INPUT_REG_MAX_NUM ) 

#define		EXCEPTION_PACKAGE_SIZE	0x05
#define		MAX_WRITE_REG_PDU_LENGTH	0x06
class commApp{
public:
	commApp();
	~commApp();
	void run();//循环接收处理程序
private:
	//检查功能码，起始地址，寄存器数量，数值是否合法
	int  check_device_addr(unsigned char *mb_req_pdu, int len);
	int  check_crc(unsigned char *mb_req_pdu, int len);
	int  check_func_code(unsigned char *mb_req_pdu, int len);
	int  check_start_addr(unsigned char *mb_req_pdu, int len);
	int  check_reg_num(unsigned char *mb_req_pdu, int len);

	int  read_input_registers(unsigned char *mb_req_pdu);//0x04　读输入寄存器
	int  exception_handle(unsigned char *received_string, int exception_code);//错误处理函数

	unsigned int crc(unsigned char * buf, int start, int cnt);
	void print_buf(unsigned char *buf, int len);
private:
	serial *myserial;
	int readParameter();
	int baud_i;			//波特率
	int dataBit;		//数据位
	char parity;		//奇偶校验
	int stopBit;		//停止位

	int start_addr;
	int end_addr;
	int max_reg_num;
	unsigned char  mb_exception_rsp[EXCEPTION_PACKAGE_SIZE];
	
	shmMem  myshm;//共享内存类对象
};

#endif
