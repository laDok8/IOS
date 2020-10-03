#include "judge.h"
void judge(int JG, int JT, Stat *info){
	do {
		mSleep(JG);
		sem_wait(info->printSem);
		fprintf(info->f, "%d\t: JUDGE \t: wants to enter \n", ++info->A);
		fflush(info->f);//bez flush spatny vypis
		sem_post(info->printSem);

		//judge enters -> block entrances
		sem_wait(info->entrSem);
		sem_wait(info->leaveSem);
		sem_wait(info->printSem);
		fprintf(info->f, "%d \t: JUDGE \t: enters \t\t: %d \t: %d \t: %d\n", ++info->A, info->NE, info->NC, info->NB);
		fflush(info->f);
		sem_post(info->printSem);
		//wait for checking imigrants
		int message = 0;
		sem_wait(info->printSem);
		if(info->NC != info->NE && info->NE != 0) {
			message = 1;
			fprintf(info->f, "%d \t: JUDGE \t: waits for imm \t: %d \t: %d \t: %d\n", ++info->A, info->NE, info->NC, info->NB);
			fflush(info->f);
			sem_post(info->printSem);
			sem_wait(info->NESem);
		}
		if(message == 0)
			sem_post(info->printSem);

		sem_wait(info->regSem);

		sem_wait(info->printSem);
		fprintf(info->f, "%d \t: JUDGE \t: starts confirmation \t: %d \t: %d \t: %d\n", ++info->A, info->NE, info->NC, info->NB);
		fflush(info->f);
		sem_post(info->printSem);
		mSleep(JT);
		sem_wait(info->printSem);
		info->IMMcounter +=  info->NC;
		//unlocks NC imigrants from loop;
		while(info->NC != 0) {
			info->NC--;
			sem_post(info->courtSem);
		}
		info->NE=0;
		fprintf(info->f, "%d \t: JUDGE \t: ends confirmation \t: %d \t: %d \t: %d\n", ++info->A, info->NE, info->NC, info->NB);
		fflush(info->f);
		sem_post(info->printSem);
		sem_post(info->regSem);

		mSleep(JT);
		sem_wait(info->printSem);
		fprintf(info->f, "%d \t: JUDGE \t: leaves \t\t: %d \t: %d \t: %d\n", ++info->A, info->NE, info->NC, info->NB);
		fflush(info->f);
		sem_post(info->printSem);
		sem_post(info->leaveSem);
		sem_post(info->entrSem);

		if(info->IMMcounter == info->mIMM)
			info->judgeRep = 0;
	}while(info->judgeRep);

	sem_wait(info->printSem);
	fprintf(info->f, "%d \t: JUDGE \t: finishes \t\t: %d \t: %d \t: %d\n", ++info->A, info->NE, info->NC, info->NB);
	fflush(info->f);
	sem_post(info->printSem);
	exit(0);
}
