#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return -1;}
	int ret;
	ret=mkdir(argv[1],0777);
	if(ret!=0){perror("mkdir");}
	return 0;
}
