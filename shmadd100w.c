#include"func.h"
#define N 1000000
int main()
{
	int shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
	int *p=(int *)shmat(shmid,NULL,0);
	*p=0;
	if(!fork())
	{
		int i;
		for(i=0;i<N;i++)*p=*p+1;
		return 0;
	}else{
		int i;
		for(i=0;i<N;i++)*p=*p+1;
		wait(NULL);
		printf("*p=%d\n",*p);
		return 0;
	}
}
