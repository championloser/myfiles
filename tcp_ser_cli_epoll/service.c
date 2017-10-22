#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=3){printf("error argc\n");return 1;}
	struct sockaddr_in seraddr;
	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(atoi(argv[2]));
	seraddr.sin_addr.s_addr=inet_addr(argv[1]);
	struct sockaddr_in cliaddr;
	memset(&cliaddr,0,sizeof(cliaddr));
	int addrlen=sizeof(cliaddr);
	char buf[128];

	int sfd=socket(AF_INET,SOCK_STREAM,0);

	int reuse=1;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,(const char*)&reuse,sizeof(int));

	bind(sfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
	listen(sfd,10);

	int epfd=epoll_create(1);
	struct epoll_event event,evs[2];
	memset(&event,0,sizeof(event));
	memset(evs,0,sizeof(evs));
	event.events=EPOLLIN;
	event.data.fd=STDIN_FILENO;
	epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
	int ret,tmpret,i;
	while(1)
	{
		int newfd=accept(sfd,(struct sockaddr*)&cliaddr,&addrlen);
		printf("connect succeed,addr=%s,port=%d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
		while(1)
		{
			event.events=EPOLLIN;
			event.data.fd=newfd;
			epoll_ctl(epfd,EPOLL_CTL_ADD,newfd,&event);
			ret=epoll_wait(epfd,evs,2,-1);
			for(i=0;i<ret;i++)
			{
				if(evs[i].data.fd==STDIN_FILENO)
				{
					memset(buf,0,sizeof(buf));
					tmpret=read(STDIN_FILENO,buf,sizeof(buf));
					if(tmpret>0)
					{send(newfd,buf,strlen(buf)-1,0);}
					else{printf("Goodbye\n");break;}
				}
				if(evs[i].data.fd==newfd)
				{
					memset(buf,0,sizeof(buf));
					tmpret=recv(newfd,buf,sizeof(buf),0);
					if(tmpret>0)
					{printf("%s\n",buf);}
					else{printf("Goodbye\n");break;}
				}
			}
			if(0==tmpret)break;
		}
		epoll_ctl(epfd,EPOLL_CTL_DEL,newfd,&event);
		close(newfd);
	}
	return 0;
}
