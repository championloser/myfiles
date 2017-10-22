#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return 1;}
	if(strcmp(argv[1],"--help")==0){printf("Example:./SendToTty.out /dev/pts/20\n");return 1;}
	int fdw=open(argv[1],O_WRONLY);
	while(1)
	{write(fdw,"Hello world\n",12);sleep(5);}
	return 0;
}
