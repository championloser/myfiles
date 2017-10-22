#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=3){printf("error argc\n");return 1;}
	struct sockaddr_in seraddr;
	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(atoi(argv[2]));
	seraddr.sin_addr.s_addr=inet_addr(argv[1]);
	int sfd=socket(AF_INET,SOCK_DGRAM,0);
	bind(sfd,(struct sockaddr*)&seraddr,sizeof(seraddr));

	struct sockaddr_in cliaddr;
	memset(&cliaddr,0,sizeof(cliaddr));
	int addrlen=sizeof(cliaddr);

	char buf[128];
	memset(buf,0,sizeof(buf));

	fd_set rdset;
	while(1)
	{
		recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&cliaddr,&addrlen);
		printf("connect succeed,addr=%s,port=%d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
		while(1)
		{
			FD_ZERO(&rdset);
			FD_SET(STDIN_FILENO,&rdset);
			FD_SET(sfd,&rdset);
			select(sfd+1,&rdset,NULL,NULL,NULL);
			if(FD_ISSET(STDIN_FILENO,&rdset))
			{
				memset(buf,0,sizeof(buf));
				if(read(STDIN_FILENO,buf,sizeof(buf))>0)
				{sendto(sfd,buf,strlen(buf)-1,0,(struct sockaddr*)&cliaddr,addrlen);}
				else{printf("Goodbye\n");break;}
			}
			if(FD_ISSET(sfd,&rdset))
			{
				memset(buf,0,sizeof(buf));
				if(recvfrom(sfd,buf,sizeof(buf),0,NULL,NULL)>0)
				{printf("%s\n",buf);}
				else{printf("Goodbye\n");break;}
			}
		}
	}
}
