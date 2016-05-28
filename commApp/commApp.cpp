#include <iostream>
#include <iomanip>
#include "sqlite3.h"
#include "commApp.h"
#include <signal.h>

using namespace std;

#define DB_PATH		"/etc/gateway/sensorConf.db"

//#define	DEBUG
commApp::commApp()
{
		cout << __func__<<endl;
#if 1
		/*初始化共享内存*/
		int i;
		for(i=0;i<=6;i++){/*input regs*/
			myshm.setval(0+i,0x02 );	
		}
#endif
		baud_i =	115200;
		dataBit = 8;
		parity = 'n';
		stopBit = 1;

}

commApp::~commApp()
{
		delete myserial;
		myserial=NULL;
		cout << __func__<<endl;

}

void commApp::run()
{
		myserial = new serial(baud_i, dataBit, parity, stopBit);
		/*test*/
		myserial->serialWrite((unsigned char *)"klhtouch start!", strlen("klhtouch start!"));

		int n, size;
		unsigned char received_string[MAX_DATA_LENGTH];
		unsigned char *p=received_string;
		while(1){
				memset(received_string, 0x0, sizeof(received_string));
				size = myserial->serialRead(received_string);
				if(size <0)
						continue;

//#ifdef DEBUG
#if 1
				cout<<"[recv "<<size<<"] ";
				for(n=0; n<size; n++)
						std::cout<<std::hex<<setw(2)<< std::setfill('0')<<(int)received_string[n]<<" ";
				std::cout <<std::endl;
#endif
				//check crc
				if(check_crc(received_string, size) < 0){
						exception_handle(received_string, 0x05);//CRC校验错误
						cout <<"crc error !" <<endl;	
						//ingore this package
						continue;
				}

				//check the function code is right or not, exception code 0x01
				if(check_func_code(received_string, size) < 0) {
						exception_handle(received_string, 0x01);
						cout << "function code is invalid !" << endl;
						continue;
				}

				//check the reg num is valid or not, exception code 0x03
				if(check_reg_num(received_string, size) < 0) {
						exception_handle(received_string, 0x03);
						cout << "reg num error !" <<endl;
						continue;
				}

				//check start address is right or not, exception code 0x02
				if(check_start_addr(received_string, size) < 0) {
						exception_handle(received_string, 0x02);
						cout << "start address error !" << endl;
						continue;
				}
				switch(received_string[1]){
						case 0x04:
								read_input_registers(received_string);
								break;
				}
				//myserial->serialWrite(p, size);
		}


}


int  commApp::check_device_addr(unsigned char *mb_req_pdu, int len)
{
#ifdef FUNC
		cout << __func__ << endl;
#endif
		if(mb_req_pdu[0] != 1)	
				return -1;

		return 0;
}


/*
 *CRC校验,低字节在前，高字节在后
 */
int  commApp::check_crc(unsigned char *mb_req_pdu, int len)
{
#ifdef FUNC
		cout << __func__ << endl;
#endif
		unsigned short crc_calc = 0;
		unsigned short crc_received = 0;

		crc_calc = crc( mb_req_pdu, 0, len - 2 );
		crc_received = (unsigned)mb_req_pdu[ len - 2 ]<<8;
		crc_received |= (unsigned)mb_req_pdu[ len - 1 ];

		return (crc_calc == crc_received) ? 0 : -1;
}

/*
 * 检查是否支持功能码, 异常码: 0x01
 */
int  commApp::check_func_code(unsigned char *mb_req_pdu, int len)
{
#ifdef FUNC
		cout << __func__ << endl;
#endif
		int reval = 0;
		switch(mb_req_pdu[1]){
				case	0x04:
						start_addr = INPUT_REG_START_ADDR;
						end_addr = INPUT_REG_END_ADDR;
						max_reg_num = INPUT_REG_MAX_NUM;
						break;
				default:
						reval = -1;

		}

		return reval;
}

/*
 * 检查起始地址是否合法, 异常码: 0x02
 */

int  commApp::check_start_addr(unsigned char *mb_req_pdu,int len)
{
#ifdef FUNC
		cout << __func__ << endl;
#endif
		int retval;
		switch(mb_req_pdu[1]){
				case 0x03:
						if(mb_req_pdu[2]==0 
										&& mb_req_pdu[3]>=start_addr
										&& mb_req_pdu[3]<=end_addr
										&& mb_req_pdu[3]+mb_req_pdu[5]<=end_addr+1) {
								retval = 0;
						}else{
								retval = -1;
						}
						break;
		}

		return retval;
}

/*
 * 检查寄存器个数是否合法, 异常码: 0x03
 */
int  commApp::check_reg_num(unsigned char *mb_req_pdu, int len)
{
#ifdef FUNC
		cout << __func__ << endl;
#endif
		int retval;
		switch(mb_req_pdu[1]){
				case 0x04:

						if(mb_req_pdu[4]==0x00&&mb_req_pdu[5] >=1 && mb_req_pdu[5] <=INPUT_REG_MAX_NUM){
								retval = 0;
						}else{
								retval = -1;
						}
						break;
		}
		return retval;
}

/***************************** [  BEGIN:  crc ] ******************************
INPUTS:
buf   ->  Array containing message to be sent to controller.            	
start ->  Start of loop in crc counter, usually 0.
cnt   ->  Amount of bytes in message being sent to controller/
OUTPUTS:
temp  ->  Returns crc byte for message.
COMMENTS:
This routine calculates the crc high and low byte of a message.
Note that this crc is only used for Modbus, not Modbus+ etc. 
 ****************************************************************************/

unsigned int commApp::crc(unsigned char *buf,int start,int cnt) 
{
#ifdef FUNC
		cout << __func__ << endl;
#endif
		int		i,j;
		unsigned	temp,temp2,flag;

		temp=0xFFFF;

		for (i=start; i<cnt; i++)
		{
				temp=temp ^ buf[i];

				for (j=1; j<=8; j++)
				{
						flag=temp & 0x0001;
						temp=temp >> 1;
						if (flag) temp=temp ^ 0xA001;
				}
		}

		/* Reverse byte order. */

		temp2=temp >> 8;
		temp=(temp << 8) | temp2;
		temp &= 0xFFFF;

		return(temp);
}

int  commApp::exception_handle(unsigned char * received_string, int exception_code)
{
		unsigned short crc_calc = 0;
		unsigned char *p=mb_exception_rsp;
		mb_exception_rsp[0] = received_string[0];
		mb_exception_rsp[1] = received_string[1]+0x80; 	
		mb_exception_rsp[2] = exception_code;
		crc_calc = crc( mb_exception_rsp, 0, EXCEPTION_PACKAGE_SIZE - 2 );
		mb_exception_rsp[3] = (crc_calc>>8) & 0xff;
		mb_exception_rsp[4] = crc_calc & 0xFF;

		myserial->serialWrite(p, EXCEPTION_PACKAGE_SIZE);

		return 0;
}

//0x04　读输入寄存器
int  commApp::read_input_registers(unsigned char *mb_req_pdu)
{
	unsigned char send_buf[MAX_RESPONSE_LENGTH], *p = send_buf;
	int start_address = mb_req_pdu[3];
	int reg_num = mb_req_pdu[5];
	int i,j,len;
	unsigned short crc_calc = 0; 

	send_buf[0] = mb_req_pdu[0]; send_buf[1] = mb_req_pdu[1];
	send_buf[2] = reg_num*2;		    
	//1、温度; 2、湿度、3、二氧化碳、4、大气压力
	//5、甲醛、6、pm2.5、7、pm10
	for(i=0; i<reg_num; i++) {
		send_buf[3+i*2] = ((myshm.getval(start_address + i))>>8)&0xFF;
		send_buf[3+i*2+1] = (myshm.getval(start_address + i))&0xFF;	
	} 

	len = 3 + send_buf[2] + 2;
	crc_calc = crc( p, 0, len - 2 );
	send_buf[len-2] = ((unsigned)crc_calc >>8)&0xFF;
	send_buf[len-1] = (unsigned)crc_calc&0xFF;

	myserial->serialWrite(p, len);
	print_buf(p, len);
	
	return 0;
}

void commApp::print_buf(unsigned char* buf, int len){
#ifdef DEBUG
	int i;
	printf("[send ] ");
	for(i=0; i<len; i++)
		printf("%.2x ", buf[i]);

	printf("\n");
#endif

}
