#include "imigrant.h"


void immigrant(int i, int IT, Stat *info){
	sem_wait(info->printSem);
	fprintf(info->f, "%d\t: IMM %d \t: starts \n", ++info->A, i);
	fflush(info->f);
	sem_post(info->printSem);

	sem_wait(info->entrSem);
	sem_wait(info->printSem);
	fprintf(info->f, "%d\t: IMM %d \t: enters  \t\t: %d \t: %d \t: %d\n", ++info->A, i, ++info->NE, info->NC, ++info->NB);
	fflush(info->f);
	//block judge access
	sem_trywait(info->NESem);
	sem_post(info->printSem);
	sem_post(info->entrSem);

	sem_wait(info->regSem);
	sem_wait(info->printSem);
	//block judge access redundant ?
	fprintf(info->f, "%d\t: IMM %d \t: checks  \t\t: %d \t: %d \t: %d\n", ++info->A, i, info->NE, ++info->NC, info->NB);
	fflush(info->f);
	if(info->NC == info->NE)
		sem_post(info->NESem);
	else
		sem_trywait(info->NESem);
	sem_post(info->printSem);
	sem_post(info->regSem);

	//waiting for judge
	sem_wait(info->courtSem);

	sem_wait(info->printSem);
	fprintf(info->f, "%d\t: IMM %d \t: wants certificate  \t: %d \t: %d \t: %d\n", ++info->A, i, info->NE, info->NC, info->NB);
	fflush(info->f);
	sem_post(info->printSem);
	mSleep(IT);
	sem_wait(info->printSem);
	fprintf(info->f, "%d\t: IMM %d \t: got certificate  \t: %d \t: %d \t: %d\n", ++info->A, i, info->NE, info->NC, info->NB);
	fflush(info->f);
	sem_post(info->printSem);

	sem_wait(info->leaveSem);
	sem_wait(info->printSem);
	fprintf(info->f, "%d\t: IMM %d \t: leaves  \t\t: %d \t: %d \t: %d\n", ++info->A, i, info->NE, info->NC, --info->NB);
	fflush(info->f);
	sem_post(info->printSem);
	sem_post(info->leaveSem);
	exit(0);
}

