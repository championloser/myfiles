#include"func.h"
void sighandler(int signum)
{
	printf("jiangjiaxian\n");
	exit(1);
}
int main()
{
	signal(SIGINT,SIG_IGN);
	while(1);
	return 0;
}
