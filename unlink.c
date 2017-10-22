#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return 1;}
	unlink(argv[1]);
	return 0;
}
