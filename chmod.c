#include<stdio.h>
#include<sys/stat.h>
int main(int argc,char *argv[])
{
	if(argc<2)
	{
		printf("error argc\n");
		return -1;
	}
	int ret;
	ret=chmod(argv[1],0755);
	if(ret!=0)
	{
		perror("chmod");
	}
	return 0;
}
