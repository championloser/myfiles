#include"func.h"
#define N 1000000
void lock(int *p)
{
	while(*p==0)
	{}
	*p=0;
}
void unlock(int *p)
{
	*p=1;
}
int main(int argc,char *argv[])
{
	if(argc!=3){printf("error argc\n");return 1;}
	key_t key1=ftok(argv[1],0);
	int shmid1=shmget(key1,4096,IPC_CREAT|0600);
	int *p1=(int *)shmat(shmid1,NULL,0);
	*p1=0;
	key_t key2=ftok(argv[2],0);
	int shmid2=shmget(key2,4096,IPC_CREAT|0600);
	int *p2=(int *)shmat(shmid2,NULL,0);
	*p2=1;
	if(!fork())
	{
		int i;
		for(i=0;i<N;i++)
		{
			lock(p2);
			*p1=*p1+1;
			unlock(p2);
		}
		return 0;
	}else{
		int i;
		for(i=0;i<N;i++)
		{
			lock(p2);
			*p1=*p1+1;
			unlock(p2);
		}
		wait(NULL);
		printf("*p1=%d\n",*p1);
		return 0;
	}
	
}
