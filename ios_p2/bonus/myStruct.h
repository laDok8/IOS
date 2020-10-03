#ifndef IOS_P2_MYSTRUCT_H
#define IOS_P2_MYSTRUCT_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include<semaphore.h>
#include <sys/stat.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>


#define mSleep(x)do{int rd = (x==0?0:(int)rand()%(x+1));\
sleep(rd/1000);\
usleep((rd%1000)*1000);\
}while(0)

typedef struct stats{
	int A;
	int NE;
	int NC;
	int NB;
	int generate;
	pid_t genPID;

	int judgeRep;
	int mIMM;
	int IMMcounter;
	FILE * f;

	sem_t *printSem;
	sem_t *entrSem;
	sem_t *regSem;
	sem_t *leaveSem;
	sem_t *courtSem;
	sem_t *NESem;
	sem_t *startSem;

} Stat;
#endif //IOS_P2_MYSTRUCT_H
