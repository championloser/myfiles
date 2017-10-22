#include"func.h"
int client_work1(int sfd)
{
	char buf[128];
	int epfd=epoll_create(1);
	struct epoll_event event,evs[2];
	memset(&event,0,sizeof(event));
	memset(evs,0,sizeof(evs));
	event.events=EPOLLIN;
	event.data.fd=STDIN_FILENO;
	epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
	event.events=EPOLLIN;
	event.data.fd=sfd;
	epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	int i,tmpret;
	int ret;
	while(1)
	{
		ret=epoll_wait(epfd,evs,2,-1);
		for(i=0;i<ret;i++)
		{
			if(evs[i].data.fd==STDIN_FILENO)
			{
				memset(buf,0,sizeof(buf));
				tmpret=read(STDIN_FILENO,buf,sizeof(buf));
				if(tmpret>0)
				{send(sfd,buf,strlen(buf)-1,0);}
				else{printf("Goodbye\n");break;}
			}
			if(evs[i].data.fd==sfd)
			{
				memset(buf,0,sizeof(buf));
				tmpret=recv(sfd,buf,sizeof(buf),0);
				if(tmpret>0)
				{printf("%s\n",buf);}
				else{printf("Goodbye\n");break;}
			}
		}
		if(0==tmpret)break;
	}

}
int client_work2(int sfd)
{
	Data train;
	memset(&train,0,sizeof(train));
	recv(sfd,&train.len,4,0);
	recv(sfd,train.buf,train.len,0);
	int fd=open(train.buf,O_CREAT|O_WRONLY,0666);
	while(recv(sfd,&train.len,4,0),train.len>0)
	{
		memset(train.buf,0,sizeof(train.buf));
		recv(sfd,train.buf,train.len,0);
		write(fd,train.buf,train.len);
	}
	recv(sfd,train.buf,sizeof(train.buf),0);//接收空包
	close(fd);
	return 0;
}
int client_work3(int sfd)
{
	Data train;
	memset(&train,0,sizeof(train));
	recv_n(sfd,&train.len,4,0);
	recv_n(sfd,train.buf,train.len,0);//接收文件名
	int fd=open(train.buf,O_CREAT|O_WRONLY,0666);
	memset(&train,0,sizeof(train));
	recv_n(sfd,&train.len,4,0);
	recv_n(sfd,train.buf,train.len,0);//接收文件长度
	long curLen,totalLen;
	curLen=0;
	totalLen=atol(train.buf);
	printf("The data size is %ld\n",totalLen);//打印文件长度
	time_t t,check;
	time(&t);
	while(recv_n(sfd,&train.len,4,0),train.len>0)
	{
		memset(train.buf,0,sizeof(train.buf));
		recv_n(sfd,train.buf,train.len,0);
		write(fd,train.buf,train.len);
		curLen=curLen+train.len;
		time(&check);
		if(check>=t+1)
		{
			pro_bar2(curLen,totalLen);
			t=check;
		}
	}
	recv_n(sfd,train.buf,sizeof(train.buf),0);//接收空包
	pro_bar2(totalLen,totalLen);
	printf("\n");
	close(fd);
	return 0;
}
int main(int argc,char *argv[])
{
	if(argc!=3){printf("error argc\n");return 1;}
	int sfd;
	int ret;
	ret=tcp_connect(&sfd,argv[1],argv[2]);
	if(ret!=0)
	{
		perror("connect");
		return 0;
	}
	printf("connect succeed\n");
	//client_work1(sfd);
	//client_work2(sfd);
	client_work3(sfd);
	close(sfd);
	return 0;
}
