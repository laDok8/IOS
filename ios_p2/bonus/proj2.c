#include "myStruct.h"
#include "judge.h"
#include "imigrant.h"
#include <signal.h>
#include <string.h>

Stat *info;

void imighandler(){
	mSleep(0);
}
void sighandler(){
	sem_wait(info->printSem);
	info->generate = 0;
	sem_post(info->printSem);
}

int init(){
	info = mmap(NULL, sizeof(Stat*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,-1,0);
	if((info->printSem = sem_open("/xdokou14_printSem",O_CREAT | O_EXCL, 666, 1)) == SEM_FAILED)
		return 1;
	if((info->entrSem = sem_open("/xdokou14_entrSem",O_CREAT | O_EXCL, 666, 1)) == SEM_FAILED)
		return 1;
	if((info->regSem = sem_open("/xdokou14_regSem",O_CREAT | O_EXCL, 666, 1)) == SEM_FAILED)
		return 1;
	if((info->leaveSem = sem_open("/xdokou14_leaveSem",O_CREAT | O_EXCL, 666, 1)) == SEM_FAILED)
		return 1;
	if((info->courtSem = sem_open("/xdokou14_courtSem",O_CREAT | O_EXCL, 666, 0)) == SEM_FAILED)
		return 1;
	if((info->NESem = sem_open("/xdokou14_NESem",O_CREAT | O_EXCL, 666, 0)) == SEM_FAILED)
		return 1;
	if((info->startSem = sem_open("/xdokou14_startSem",O_CREAT | O_EXCL, 666, 0)) == SEM_FAILED)
		return 1;
	return 0;
}
void clean(){
	sem_close(info->printSem);
	sem_close(info->entrSem);
	sem_close(info->regSem);
	sem_close(info->leaveSem);
	sem_close(info->courtSem);
	sem_close(info->NESem);
	sem_close(info->startSem);
	sem_unlink("/xdokou14_printSem");
	sem_unlink("/xdokou14_entrSem");
	sem_unlink("/xdokou14_regSem");
	sem_unlink("/xdokou14_leaveSem");
	sem_unlink("/xdokou14_courtSem");
	sem_unlink("/xdokou14_NESem");
	sem_unlink("/xdokou14_startSem");
	munmap(info, sizeof(Stat*));
}

void createImigrant(int PI, int JG, int IT, Stat *info){
	do {
		info->mIMM += PI;
		sem_post(info->startSem);
		//pid_t pidarr[PI];
		//imigrant id
		pid_t pid = getpid();
		info->genPID = pid;
		int id = 0;
		for (int i = 0; i < PI; i++) {
			mSleep(JG);
			pid = fork();
			if (pid == -1) {
				perror("chyba fork");
				exit(1);
			}
			if (pid == 0) {
				id = i + 1;
				//pidarr[i] = getpid();
				immigrant(id, IT, info);
			}
		}
		signal(SIGINT, imighandler);
		//wait for children to send signal
		pause();
	}while(info->generate);
	exit(0);
}

int main(int argc,char **argv){
	//geting arguments
	srand(time(0));
	errno=0;
	int RT=0;
	int pom = (argc == 8) ? 1 : 0;//should i generate procesess ?
	char *errstr;
	if(!(argc == 8 || argc == 6)) {
		perror("arg error");
		return 1;
	}
	//-b
	if(argc == 8 ){
		if(!strcmp(argv[1],"-b"))
			RT = strtol(argv[2],&errstr,10);
		if(RT < 1 || RT > 7000){
			perror("RT wrong");
			exit(1);
		}
		//shift argv so rest of the code is untouched
		for(int i=0;i<6;i++)
			argv[i]=argv[i+2];
	}
	int PI=strtol(argv[1],&errstr,10);
	if(*errstr != 0 || errno!=0 || PI < 1)
		return 1;
	int arg[4];// IG JG IT JT
	for (int i = 0; i < 4; ++i) {
		arg[i] = strtol(argv[2+i],&errstr,10);
		if(*errstr != 0 || errno != 0 || arg[i] < 0 || arg[i] > 2000)
			return 1;
	}
	//init memory & semaphor
	if(init() != 0) {
		clean();
		perror("memory not cleaned");
		return 1;
	}
	pid_t pidarr[2];
	info->judgeRep=1;//while loop
	info->mIMM = 0;
	info->generate = pom;
	pid_t pid = getpid();

	//file init
	info->f = fopen("proj2.out","w");
	if(info->f == NULL){
		perror("file open error");
		return 1;
	}

	//process to create imigrants
	pid = fork();
	if(pid == -1){
		perror("chyba fork");
		exit(1);
	}
	if(pid == 0){
		pidarr[0] = getpid();
		createImigrant(PI, arg[1], arg[2], info);
	}

	//create judge
	pid = fork();
	if(pid == -1){
		perror("chyba fork");
		exit(1);
	}
	if(pid == 0){
		pidarr[1] = getpid();
		judge(arg[1], arg[3], info);
	}

	if(RT != 0){
		signal(SIGQUIT, sighandler);
		mSleep(RT);
		sighandler();
	}
	//wait for children to die
	for(int i=0;i<PI;i++){
		wait(&pidarr[i]);
	}
	fclose(info->f);
	clean();
	return 0;
}