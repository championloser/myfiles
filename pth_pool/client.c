#include"pthread_pool.h"
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
	recv_file(sfd);//收文件
	close(sfd);
	return 0;
}
