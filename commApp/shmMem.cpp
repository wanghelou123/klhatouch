#include "shmMem.h"

shmMem::shmMem()
{

	/*映射共享内存*/
	if((shmid = (shmget(SHMKEY, SHM_NUM, 0666|IFLAGS))) == -1){
		perror("shmget:\n");
	}

	shmptr = (int*)shmat(shmid, 0, 0);
	if(shmptr == (void*)-1 )
		perror("shmat error\n");
}

shmMem::~shmMem()
{
	if(shmdt(shmptr) == -1)
		perror("shmdt error\n");
	
//	if (shmctl(shmid, IPC_RMID, 0) < 0)
//		perror("shmctl error\n");
}


int shmMem::getval(int channel)
{
	return shmptr[channel];
}


int shmMem::setval(int channel, int val)
{
	shmptr[channel] = val&0xffff;

	return 0;
}

