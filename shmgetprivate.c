#include"func.h"
int main()
{
	int shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
	char *p=shmat(shmid,NULL,0);
	if(!fork())
	{
		printf("Child:%s\n",p);
	}else{
		sprintf(p,"%s","jiang jiaxian");
		wait(NULL);
		return 0;
	}
}
