#include"func.h"
int main(int argc,char* argv[])
{
	if(argc!=2){printf("error argc\n");return 1;}
	struct hostent* p;
	p=gethostbyname(argv[1]);
	printf("h_name=%s\n",p->h_name);
	int i=0;
	while(p->h_aliases[i]!=NULL)
	{
		printf("h_aliase=%s\n",p->h_aliases[i]);
		i++;
	}
	i=0;
	char addr[16];
	while(p->h_addr_list[i]!=NULL)
	{
		inet_ntop(p->h_addrtype,p->h_addr_list[i],addr,sizeof(addr));
		printf("%s\n",addr);
		i++;
	}
	return 0;
}
