#include"func.h"
int main()
{
	mkfifo("file1.pipe",0600);
	mkfifo("file2.pipe",0600);
	int fdr=open("file1.pipe",O_RDONLY);
	int fdw=open("file2.pipe",O_WRONLY);
	int pid=getpid();
	char buf[512];
	//printf("I am process a,my pid=%d\n",pid);
	memset(buf,0,sizeof(buf));
	sprintf(buf,"%d",pid);             //将pid由管道2发送给b进程
	write(fdw,buf,strlen(buf));
	memset(buf,0,sizeof(buf));
	read(fdr,buf,sizeof(buf));         //从管道1中读取b进程的pid
	int bpid=atoi(buf);
	//printf("The pid of b is %d\n",bpid);
	
	int shmid=shmget(1234,4096,IPC_CREAT|0600);	//创建一块共享内存
	Nodepoint p=(Nodepoint)shmat(shmid,NULL,0);
	memset(p,0,sizeof(p));

	fd_set fdset;
	while(1)
	{
		system("clear");
		FD_ZERO(&fdset);
		FD_SET(STDIN_FILENO,&fdset);
		FD_SET(fdr,&fdset);
		select(fdw+1,&fdset,NULL,NULL,NULL);
		if(FD_ISSET(STDIN_FILENO,&fdset))
		{
			memset(buf,0,sizeof(buf));
			if(read(STDIN_FILENO,buf,sizeof(buf))>0)
			{
				write(fdw,buf,strlen(buf));
				memset(p,0,sizeof(p));
				p->flag='A';
				strcpy(p->buf,buf);
			}else{
				printf("Goodbye\n");break;
			}
		}
		if(FD_ISSET(fdr,&fdset))
		{
			memset(buf,0,sizeof(buf));
			if(read(fdr,buf,sizeof(buf))>0)
			{
				memset(p,0,sizeof(p));
				p->flag='B';
				strcpy(p->buf,buf);
			}else{
				printf("Goodbye\n");break;
			}
		}
	}
	close(fdr);
	close(fdw);
	shmctl(shmid,IPC_RMID,NULL);
	unlink("file1.pipe");
	unlink("file2.pipe");
	p->flag='E';
	return 0;
}
