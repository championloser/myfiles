#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=4){printf("error argc\n");return 0;}
	int sfd;
	tcp_listen(&sfd,argv[1],argv[2]);//监听端口
	//tcp_listen(int *sfd,char *ip,char *port);
	
	struct sockaddr_in cliaddr;
	memset(&cliaddr,0,sizeof(cliaddr));
	int addrlen=sizeof(cliaddr);
	int new_fd; 

	int childNum=atoi(argv[3]);
	Nodepoint childInfo=(Nodepoint)calloc(childNum,sizeof(Node));
	int epfd;
	create_child(&sfd,&epfd,childInfo,childNum);//创建所有子进程并注册信息
	//create_child(int *sfd,int *epfd,Nodepoint childInfo,int childNum);

	struct epoll_event *evs=(struct epoll_event*)calloc(childNum+1,sizeof(struct epoll_event));
	int ret,tmpret,i,j;
	char flag;
	while(1)
	{
		ret=epoll_wait(epfd,evs,childNum+1,-1);
		for(i=0;i<ret;i++)
		{
			if(evs[i].data.fd==sfd)
			{
				new_fd=accept(sfd,(struct sockaddr*)&cliaddr,&addrlen);
				printf("Parent:client ip=%s,port=%d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
				for(j=0;j<childNum;j++)
				{
					if(childInfo[j].busy==0)
					{
						send_fd(childInfo[j].tfd,&new_fd);//向子进程发送文件描述符
						childInfo[j].busy=1;
						printf("Parent:child %d is busy\n",childInfo[j].pid);
						break;
					}
				}
				close(new_fd);
			}
			for(j=0;j<childNum;j++)
			{
				if(evs[i].data.fd==childInfo[j].tfd)
				{
					childInfo[j].busy=0;
					recv(childInfo[j].tfd,&flag,1,0);
					printf("Parent:child %d is not busy\n",childInfo[j].pid);
					break;
				}
			}
		}
	}
}
