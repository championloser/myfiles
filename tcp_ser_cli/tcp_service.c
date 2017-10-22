#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=3){printf("error argc\n");return 1;}
	int sfd=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in my_addr;
	memset(&my_addr,0,sizeof(my_addr));
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(atoi(argv[2]));
	my_addr.sin_addr.s_addr=inet_addr(argv[1]);
	bind(sfd,(struct sockaddr*)&my_addr,sizeof(my_addr));

	listen(sfd,10);

	struct sockaddr_in addr;
	int addrlen;
	addrlen=sizeof(addr);
	int new_fd=accept(sfd,(struct sockaddr*)&addr,&addrlen);
	printf("I am service,accept successed\n");
	printf("The client ip=%s,port=%d\n",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));

	char buf[128];
	memset(buf,0,sizeof(buf));
	recv(new_fd,buf,sizeof(buf),0);
	printf("%s\n",buf);
	send(new_fd,"hello",5,0);
	while(1);
}
