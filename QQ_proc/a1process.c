#include"func.h"
int main()
{
	int shmid=shmget(1234,4096,IPC_CREAT|0600);
	Nodepoint p=(Nodepoint)shmat(shmid,NULL,0);
	system("clear");
	while(1)
	{
		if(p->flag=='E')
		{
			printf("Goodbye\n");
			break;
		}
		if(p->flag=='A' || p->flag=='B')
		{
			printf("%c:%s",p->flag,p->buf);
			p->flag='C';
		}
	}
	return 0;
}
