#include"func.h"
int main(int argc,char *argv[])
{
	int begin=time(NULL);
	if(argc!=3){printf("error argc\n");return 0;}
	int fd1=open(argv[1],O_RDWR);
	int fd2=open(argv[2],O_RDWR);
	long int len=90243352;
	int ret;
	ret=lseek(fd2,len,SEEK_SET);
	printf("ret=%d\n",ret);
	write(fd2,"c",1);
	lseek(fd2,0,SEEK_SET);
	char *p1=(char*)mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd1,0);
	char *p2=(char*)mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd2,0);
	int i;
	for(i=0;i<len;i++)
	{
		p2[i]=p1[i];
	}
	munmap(p1,len);
	munmap(p2,len);
	int end=time(NULL);
	printf("time=%d\n",end-begin);
	return 0;
}
