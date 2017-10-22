#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=3){printf("error argc\n");return 1;}
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in ser_addr;
	memset(&ser_addr,0,sizeof(ser_addr));
	ser_addr.sin_family=AF_INET;
	ser_addr.sin_port=htons(atoi(argv[2]));
	ser_addr.sin_addr.s_addr=inet_addr(argv[1]);
	connect(sfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));

	send(sfd,"I am client",11,0);
	char buf[128];
	memset(buf,0,sizeof(buf));
	recv(sfd,buf,sizeof(buf),0);
	printf("%s\n",buf);
	while(1);
}
