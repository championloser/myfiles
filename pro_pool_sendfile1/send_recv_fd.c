#include"func.h"
int send_fd(int tfd,int *new_fd)
{
	struct msghdr msg;
	memset(&msg,0,sizeof(msg));
	
	struct iovec msg_iov;
	memset(&msg_iov,0,sizeof(msg_iov));
	char buf[]="hello";
	msg_iov.iov_base=buf;
	msg_iov.iov_len=strlen(buf);
	msg.msg_iov=&msg_iov;
	msg.msg_iovlen=1;

	int len=CMSG_LEN(sizeof(int)*1);
	struct cmsghdr *cmsg=(struct cmsghdr*)calloc(1,len);
	cmsg->cmsg_len=len;
	cmsg->cmsg_level=SOL_SOCKET;
	cmsg->cmsg_type=SCM_RIGHTS;
	*(int *)CMSG_DATA(cmsg)=*new_fd;
	msg.msg_control=cmsg;
	msg.msg_controllen=len;

	sendmsg(tfd,&msg,0);
	
	return 0;
}
int recv_fd(int tfd,int *new_fd)
{
	struct msghdr msg;
	memset(&msg,0,sizeof(msg));
	
	struct iovec msg_iov;
	memset(&msg_iov,0,sizeof(msg_iov));
	char buf[]="hello";
	msg_iov.iov_base=buf;
	msg_iov.iov_len=strlen(buf);
	msg.msg_iov=&msg_iov;
	msg.msg_iovlen=1;

	int len=CMSG_LEN(sizeof(int)*1);
	struct cmsghdr *cmsg=(struct cmsghdr*)calloc(1,len);
	cmsg->cmsg_len=len;
	cmsg->cmsg_level=SOL_SOCKET;
	cmsg->cmsg_type=SCM_RIGHTS;
	msg.msg_control=cmsg;
	msg.msg_controllen=len;

	recvmsg(tfd,&msg,0);
	*new_fd=*(int *)CMSG_DATA(cmsg);
	
	return 0;
}
