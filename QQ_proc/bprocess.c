#include"func.h"
int main()
{
	mkfifo("file1.pipe",0600);
        mkfifo("file2.pipe",0600);
	int fdw=open("file1.pipe",O_WRONLY);
	int fdr=open("file2.pipe",O_RDONLY);
	int pid=getpid();
	//printf("I am process b,pid=%d\n",pid);
	char buf[512];
	memset(buf,0,sizeof(buf));
	read(fdr,buf,sizeof(buf));	//从管道2中获取a进程的pid
	int apid=atoi(buf);
	//printf("The pid of a is %d\n",apid);
	memset(buf,0,sizeof(buf));
	sprintf(buf,"%d",pid);
	write(fdw,buf,strlen(buf));	//由管道1将pid发送给a进程
	fd_set fdset;

	int shmid=shmget(1235,4096,IPC_CREAT|0600);	//创建一块共享内存
	Nodepoint p=(Nodepoint)shmat(shmid,NULL,0);
	memset(p,0,sizeof(p));

	while(1)
	{
		system("clear");
		FD_ZERO(&fdset);
		FD_SET(STDIN_FILENO,&fdset);
		FD_SET(fdr,&fdset);
		select(fdr+1,&fdset,NULL,NULL,NULL);
		if(FD_ISSET(STDIN_FILENO,&fdset))
		{
			memset(buf,0,sizeof(buf));
			if(read(STDIN_FILENO,buf,sizeof(buf))>0)
			{
				write(fdw,buf,strlen(buf));
				memset(p,0,sizeof(p));
				p->flag='B';
				strcpy(p->buf,buf);
			}else{
				p->flag='E';
				printf("Goodbye\n");break;
			}
		}
		if(FD_ISSET(fdr,&fdset))
		{
			memset(buf,0,sizeof(buf));
			if(read(fdr,buf,sizeof(buf))>0)
			{
				memset(p,0,sizeof(p));
				p->flag='A';
				strcpy(p->buf,buf);
			}else{
				p->flag='E';
				printf("Goodbye\n");break;
			}
		}
	}
	close(fdr);
	close(fdw);
	shmctl(shmid,IPC_RMID,NULL);
	p->flag='E';
	return 0;
}
