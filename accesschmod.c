#include"func.h"
unsigned int Translate(unsigned int tmpmode)
{
	unsigned int mode;
	unsigned int a=tmpmode%10;
	unsigned int b=(tmpmode%100)/10;
	unsigned int c=tmpmode/100;
	mode=c*64+b*8+a;
	return mode;
}
int main(int argc,char *argv[])
{
	if(argc!=3){printf("error argc\n");return 1;}
	unsigned int tmpmode=atoi(argv[1]);
	if(tmpmode<100 || tmpmode>777){printf("error argc1\n");return 2;}
	unsigned int mode=Translate(tmpmode);
	chmod(argv[2],mode);
	return 0;
}
