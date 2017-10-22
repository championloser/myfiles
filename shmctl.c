#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=2){printf("errror argc\n");return 1;}
	key_t key=ftok(argv[1],0);
	int shmid=shmget(key,4096,IPC_CREAT|0600);
	struct shmid_ds buf;
	memset(&buf,0,sizeof(buf));
	shmctl(shmid,IPC_STAT,&buf);
	printf("uid=%d,cpid=%d,size=%ld,attch=%ld\n",buf.shm_perm.uid,buf.shm_cpid,buf.shm_segsz,buf.shm_nattch);
	buf.shm_perm.mode=0660;
	shmctl(shmid,IPC_SET,&buf);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
