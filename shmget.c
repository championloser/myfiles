#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return 1;}
	key_t key=ftok(argv[1],0);
	int shmid=shmget(key,4096,IPC_CREAT|0600);
	char *p=(char *)shmat(shmid,NULL,0);
	strcpy(p,"hello");
	return 0;
}
