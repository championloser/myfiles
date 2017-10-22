#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return 0;}
	int fd=open(argv[1],O_RDWR);
	char *p;
	p=mmap(NULL,5,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	p[1]='H';
	munmap(p,5);
	return 0;
}
