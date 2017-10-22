#include<stdio.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return -1;}
	puts(getcwd(NULL,0));
	chdir(argv[1]);
	puts(getcwd(NULL,0));
	return 0;
}
