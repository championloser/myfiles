#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return -1;}
	int fd=open(argv[1],O_RDWR);
	ftruncate(fd,1024);
	close(fd);
	return 0;
}
