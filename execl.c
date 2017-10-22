#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=3){printf("error argc\n");return 1;}
	execl("./add.out","add.out",argv[1],argv[2],NULL);
	return 0;
}
