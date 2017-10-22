#include"func.h"
#define N 1000000
//void lock(int *p)
//{
//	while(*p==0)
//	{}
//	*p=0;
//}
//void unlock(int *p)
//{
//	*p=1;
//}
int main(int argc,char *argv[])
{
	int shmid1=shmget(1234,4096,IPC_CREAT|0600);
	int *p1=(int *)shmat(shmid1,NULL,0);
	*p1=0;
	//key_t key2=ftok(argv[2],0);
	//int shmid2=shmget(key2,4096,IPC_CREAT|0600);
	//int *p2=(int *)shmat(shmid2,NULL,0);
	//*p2=1;
	if(!fork())
	{
		int i;
		for(i=0;i<N;i++)
		{
			++*p1;
		}
		return 0;
	}else{
		int i;
		for(i=0;i<N;i++)
		{
			++*p1;
		}
		wait(NULL);
		printf("*p1=%d\n",*p1);
		return 0;
	}
	
}
