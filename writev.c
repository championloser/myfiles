#include"func.h"
int main()
{	
	int fd=open("file",O_RDWR);
	struct iovec iov[2];
	memset(iov,0,sizeof(iov));
	char buf1[]="hello";
	char buf2[]="world";
	iov[0].iov_base=buf1;
	iov[0].iov_len=strlen(buf1);
	iov[1].iov_base=buf2;
	iov[1].iov_len=strlen(buf2);
	writev(fd,iov,2);
	close(fd);
	return 0;
}
