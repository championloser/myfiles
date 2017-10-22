#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=3){printf("error argc\n");return 1;}
	char *str[4];
	str[0]="add.out";
	str[1]=argv[1];
	str[2]=argv[2];
	str[3]=NULL;
	execv("./add.out",str);
	return 0;
}
