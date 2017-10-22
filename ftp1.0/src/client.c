#include"pthread_pool.h"
int main(int argc,char *argv[])
{
	char *address;
	char *port;
	char *logfile;
	int ret,pthnum;
	if(argc>=3)//如果用户没有输入ip和端口号则从配置文件中获取
	{
		address=argv[1];
		port=argv[2];
	}else{
		ret=get_addr_port(&address,&port,&pthnum,&logfile);//从配置信息中获取IP端口
		if(ret!=0){printf("get configuration information error!\n");return -1;}
	}

	int sfd;
	ret=tcp_connect(&sfd,address,port);
	if(ret!=0)
	{
		perror("connect");
		return 0;
	}
	printf("connect successfully\n");
	ftp_work_client(sfd);//ftp客户端功能函数
	close(sfd);
	return 0;
}
