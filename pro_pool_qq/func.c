#include"func.h"
int child_work(int new_fd)
{
	char buf[128];
	int pid=getpid();
	int ret;
	while(1)
	{
		ret=recv(new_fd,buf,sizeof(buf),0);
		if(ret>0)
		{
			memset(buf,0,sizeof(buf));
			sprintf(buf,"Child:my pid is %d",pid);
			send(new_fd,buf,strlen(buf),0);
		}else{
			break;
		}
	}
}
int create_child(int *sfd,int *epfd,Nodepoint childInfo,int childNum)
{
	int i;
	int tfds[2];
	int pid;
	char flag='E';
	for(i=0;i<childNum;i++)
	{
		socketpair(AF_LOCAL,SOCK_STREAM,0,tfds);
		pid=fork();
		if(!pid)
		{
			close(tfds[1]);
			int new_fd;
			while(1)
			{
				recv_fd(tfds[0],&new_fd);//子进程接收文件描述符
				child_work(new_fd);	//子进程开始工作
				close(new_fd);
				send(tfds[0],&flag,1,0);//子进程工作完毕，向父进程发送信号
			}
		}
		close(tfds[0]);
		childInfo[i].pid=pid;
		childInfo[i].tfd=tfds[1];
		childInfo[i].busy=0;
	}
	*epfd=epoll_create(1);
	struct epoll_event event;
	event.events=EPOLLIN;
	event.data.fd=*sfd;
	epoll_ctl(*epfd,EPOLL_CTL_ADD,*sfd,&event);//注册sfd
	for(i=0;i<childNum;i++)
	{
		event.data.fd=childInfo[i].tfd;
		epoll_ctl(*epfd,EPOLL_CTL_ADD,childInfo[i].tfd,&event);//循环注册tfd
	}
	
	for(i=0;i<childNum;i++)
	{
		printf("child %d pid=%d\n",i,childInfo[i].pid);
	}
	return 0;
}
