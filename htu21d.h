//All the following is from the htu21df manual
#ifndef __HTU21D_H
#define __HTU21D_H
#define HTU21DF_I2CADDR    0x40
#define HTU21DF_READTEMP   0xF3 //No Hold
#define HTU21DF_READHUM    0xF5 //No Hold
#define HTU21DF_WRITEREG   0xE6
#define HTU21DF_READREG    0xE7
#define HTU21DF_RESET      0xFE

class htu21d {
private:
	int         i2c_Open             (char *I2CBusName);
	void        i2c_commonsenderror  (int fd, unsigned char  DeviceAddress);
	int         htu21df_crcdata      (const unsigned char  *Data, unsigned short *ConvertedValue);
	int         htu21df_ReadUserReg  (int fd, int *retValue);
	int         htu21df_WriteUserReg (int fd,int NewValue);
	int         htu21df_init         (int fd);
	int         htu21df_getValue     (int fd, float *Value, const unsigned char  YourBiddingMaster );
	float       htu21df_compensatedRH(float RH,float TempCell);
	float       htu21df_pptamb       (float Temp);
	float       htu21df_DewPoint     (float Temp, float Hum);
private:
	int fd;
	int HTU21DF_ResetDelay;
	int HTU21DF_MinDelay; //Should be 16-RetryDelay (16 or so for hum 50 for temp)
	int HTU21DF_RetryDelay; 

	float htu21df_ACo;
	float htu21df_BCo;
	float htu21df_CCo;
public:
	htu21d();
	~htu21d();
	int get_temperature();
	int get_humidity();
};
#endif
