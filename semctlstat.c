#include"func.h"
int main()
{
	int semid=semget(1234,1,IPC_CREAT|0600);
	struct semid_ds buf;
	semctl(semid,0,IPC_STAT,&buf);
	printf("cuid=%lu,mode=%o,nsems=%ld\n",buf.sem_perm.cuid,buf.sem_perm.mode,buf.sem_nsems);
	return 0;
}
