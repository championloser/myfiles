#include"func.h"
#define N 1000000
int main(int argc,char *argv[])
{
	int shmid1=shmget(1234,4096,IPC_CREAT|0600);
	int *p1=(int *)shmat(shmid1,NULL,0);
	*p1=0;
	int semid=semget(1234,1,IPC_CREAT|0600);
	semctl(semid,0,SETVAL,1);
	struct sembuf sopp,sopv;
	sopp.sem_num=0;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num=0;
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;
	if(!fork())
	{
		int i;
		for(i=0;i<N;i++)
		{
			semop(semid,&sopp,1);
			*p1=*p1+1;
			semop(semid,&sopv,1);
		}
		return 0;
	}else{
		int i;
		for(i=0;i<N;i++)
		{
			semop(semid,&sopp,1);
			*p1=*p1+1;
			semop(semid,&sopv,1);
		}
		wait(NULL);
		printf("*p1=%d\n",*p1);
		return 0;
	}
	
}
