#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=3){printf("error argc\n");return -1;}
	int fdw=open(argv[1],O_WRONLY);//打开管道1的写端
	int fdr=open(argv[2],O_RDONLY);//打开管道2的读端
	printf("I am writer\n");
	char buf[128];
	fd_set fdset;
	int ret;
	while(1)
	{
		FD_ZERO(&fdset);
		FD_SET(0,&fdset);
		FD_SET(fdr,&fdset);
		select(fdr+1,&fdset,NULL,NULL,NULL);
		if(FD_ISSET(fdr,&fdset))
		{
			memset(buf,0,sizeof(buf));
			ret=read(fdr,buf,sizeof(buf));//从管道2中读入数据
			if(ret>0)printf("%s\n",buf);
			else{printf("Goodbye\n");break;}
		}
		if(FD_ISSET(STDIN_FILENO,&fdset))
		{
			memset(buf,0,sizeof(buf));
			ret=read(STDIN_FILENO,buf,sizeof(buf));
			if(ret>0)write(fdw,buf,strlen(buf)-1);//向管道1中写入数据
			else{printf("Goodbye\n");break;}
		}
	}
	close(fdr);
	close(fdw);
	return 0;
}
