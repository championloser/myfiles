#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return -1;}
	umask(0);
	int fd=open(argv[1],O_RDONLY|O_CREAT|O_EXCL,0777);
	if(-1==fd){perror("open");return -1;}
	printf("fd=%d\n",fd);
	return 0;
}
