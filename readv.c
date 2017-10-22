#include"func.h"
int main()
{	
	int fd=open("file",O_RDWR);
	struct iovec iov[2];
	memset(iov,0,sizeof(iov));
	char buf1[10];
	char buf2[10];
	memset(buf1,0,sizeof(buf1));
	memset(buf2,0,sizeof(buf2));
	iov[0].iov_base=buf1;
	iov[0].iov_len=6;
	iov[1].iov_base=buf2;
	iov[1].iov_len=4;
	readv(fd,iov,2);
	printf("buf1=%s,buf2=%s\n",buf1,buf2);
	close(fd);
	return 0;
}
