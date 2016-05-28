# 一个通用的Makefile
#	wanghelou
#	2012-12-4


# $@:	规则的目标文件名
# $^:	所有依赖的名字,名字之间用空格隔开
# $<:	第一个依赖的文件名
# $(patsubst pattern, replacement, text):	寻找"text"中符合格式"pattern"的字，　
#		用"replacement" 替换他空。"pattern"和“replacement”中可以使用能配置符
TARGET = collector
all: $(TARGET)
CROSS_COMPILE = arm-linux-
CC		=	$(CROSS_COMPILE)g++
STRIP	=	$(CROSS_COMPILE)strip
CFLAGS	=	-W
INCS   +=	-I/work/src_packages/sqlite-autoconf-3071401/dist-sqlite3/include 
INCS 	+=  -I/usr/local/arm/4.2.2-eabi/include
LIBS	+=	-L/work/src_packages/sqlite-autoconf-3071401/dist-sqlite3/lib 
LIBS	+=	-lsqlite3 
LIBS 	+=  -llog4cplus
LIBS 	+=  -lpthread
LIBS 	+=  -lm

collector: collector.o Log.o serial.o co2Sensor.o ch2oSensor.o pm2_5Sensor.o sht11.o htu21d.o shmMem.o
	$(CC) $(CFLAGS) $(LIBS) $(INCS) -o $@ $^ 
	$(STRIP) $@

%.o:%.cpp
	$(CC) $(CFLAGS)  $(INCS) -c -o $@ $<

clean:
	rm -f  $(TARGET) *.o
