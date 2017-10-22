#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return 1;}
	int fd=open(argv[1],O_RDWR);
	char buf[128];
	memset(buf,0,sizeof(buf));
	scanf("%s",buf);
	write(fd,buf,strlen(buf));
	close(fd);
	return 0;
}
