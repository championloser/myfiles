#include<stdio.h>
#include<arpa/inet.h>
int main()
{
	short port=0x1234;
	printf("port=%x\n",port);
	short j=htons(port);
	printf("port=%x\n",j);
	short i=ntohs(j);
	printf("port=%x\n",i);
	return 0;
}
