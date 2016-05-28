#include <iostream>
#include <iomanip>
#include <setjmp.h>
#include "commApp.h"
#include "serial.h"
#include <signal.h>

using namespace std;

static sigjmp_buf	jmpbuf;
commApp *pApp;

void  sigUsr(int signo)
{
		if(signo == SIGUSR1){
				cout << "received SIGUSR1"<<endl;
				siglongjmp(jmpbuf, 1);
		}
}
void show_prog_info()
{
	cout << "kl-htouch function board Software, Inc."<<endl;
	cout << "Program name commApp run with hardware V5." << endl;
	cout << "Compiled on " << __DATE__ << " at "<< __TIME__ <<endl;
}
int main()
{
		if(signal(SIGUSR1, sigUsr) == SIG_ERR)
				perror("can't catch SIGUSR1\n");

		if(sigsetjmp(jmpbuf,1)){
				//pApp->~commApp();
				delete pApp;
				printf("restart the program!\n");	
				//exit(0);
		}

		show_prog_info();

		pApp = new commApp();
		try{
				pApp->run();
		}catch(...){
				printf("error\n");
		}

		printf("end\n");

		return 0;
}
