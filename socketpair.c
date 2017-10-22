#include"func.h"
void send_fd(int fds,int fd)
{
	struct msghdr msg;
	memset(&msg,0,sizeof(msg));

	struct iovec iov[2];
	char buf1[10]="hello";
	char buf2[10]="world";
	iov[0].iov_base=buf1;
	iov[0].iov_len=strlen(buf1);
	iov[1].iov_base=buf2;
	iov[1].iov_len=strlen(buf2);
	msg.msg_iov=iov;
	msg.msg_iovlen=2;
	
	struct cmsghdr *cmsg=(struct cmsghdr*)malloc(CMSG_LEN(sizeof(int)));
	cmsg->cmsg_level=SOL_SOCKET;
	cmsg->cmsg_type=SCM_RIGHTS;
	cmsg->cmsg_len=CMSG_LEN(sizeof(int));
	*(int *)CMSG_DATA(cmsg)=fd;
	msg.msg_control=cmsg;
	msg.msg_controllen=CMSG_LEN(sizeof(int));

	sendmsg(fds,&msg,0);
}
void recv_fd(int fds,int *fd)
{
	struct msghdr msg;
	memset(&msg,0,sizeof(msg));

	struct iovec iov[2];
	char buf1[10]="hello";
	char buf2[10]="world";
	iov[0].iov_base=buf1;
	iov[0].iov_len=strlen(buf1);
	iov[1].iov_base=buf2;
	iov[1].iov_len=strlen(buf2);
	msg.msg_iov=iov;
	msg.msg_iovlen=2;
	
	struct cmsghdr *cmsg=(struct cmsghdr*)malloc(CMSG_LEN(sizeof(int)));
	cmsg->cmsg_level=SOL_SOCKET;
	cmsg->cmsg_type=SCM_RIGHTS;
	cmsg->cmsg_len=CMSG_LEN(sizeof(int));
	msg.msg_control=cmsg;
	msg.msg_controllen=CMSG_LEN(sizeof(int));

	recvmsg(fds,&msg,0);
	*fd=*(int *)CMSG_DATA(cmsg);
}
int main()
{
	int fds[2];
	int sockfd=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
	if(!fork())
	{
		close(fds[1]);
		int fd;
		recv_fd(fds[0],&fd);
		printf("child:fd=%d\n",fd);
		char buf[10];
		memset(buf,0,sizeof(buf));
		lseek(fd,0,SEEK_SET);
		read(fd,buf,sizeof(buf));
		printf("buf=%s\n",buf);
		return 0;
	}else{
		close(fds[0]);
		int fd=open("file",O_RDWR);
		write(fd,"hello",5);
		printf("parent:fd=%d\n",fd);
		send_fd(fds[1],fd);
		wait(NULL);
		return 0;
	}
}
