#include"tcp.h"
int tcp_listen(int *sfd,char *ip,char *port)
{
	*sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in seraddr;
	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(atoi(port));
	seraddr.sin_addr.s_addr=inet_addr(ip);

	int ret;
	ret=bind(*sfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
	if(-1==ret)return -1;
	ret=listen(*sfd,MAXLINK);
	if(-1==ret)return -1;
	return 0;
}
int tcp_connect(int *sfd,char *ip,char *port)
{
	*sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in seraddr;
	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(atoi(port));
	seraddr.sin_addr.s_addr=inet_addr(ip);
	int ret=connect(*sfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
	return ret;
}
