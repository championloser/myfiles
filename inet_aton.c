#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return 1;}
	struct in_addr addr;
	inet_aton(argv[1],&addr);
	printf("addr=%x\n",addr.s_addr);
	return 0;
}
