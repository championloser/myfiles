#include"func.h"
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
	close(sfd);
	return 0;
}
