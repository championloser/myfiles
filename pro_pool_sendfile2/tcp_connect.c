#include"func.h"
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
