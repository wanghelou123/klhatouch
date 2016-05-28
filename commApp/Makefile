# 一个通用的Makefile
#	wanghelou
#	2012-12-4


# $@:	规则的目标文件名
# $^:	所有依赖的名字,名字之间用空格隔开
# $<:	第一个依赖的文件名
# $(patsubst pattern, replacement, text):	寻找"text"中符合格式"pattern"的字，　
#		用"replacement" 替换他空。"pattern"和“replacement”中可以使用能配置符

APP		=	commApp
CC		=	arm-linux-g++
CFLAGS	=	-W 
INCS	= 	-I/work/src_packages/sqlite-autoconf-3071401/dist-sqlite3/include
LIBS	=	-L/work/src_packages/sqlite-autoconf-3071401/dist-sqlite3/lib -lsqlite3
src		:= 	$(shell ls *.cpp)
objs	:=	$(patsubst %.cpp,%.o,$(src))

$(APP):$(objs)
	$(CC) $(CFLAGS) $(LIBS) $(INCS) -o $@ $^

%.o:%.cpp 
	$(CC) $(CFLAGS)  $(LIBS) $(INCS) -c -o $@ $<

clean:
	rm -f $(APP) *.o
