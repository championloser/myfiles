#include"func.h"
void sighandler(int signum)
{
	printf("before:I am signal %d\n",signum);
	sleep(3);
	printf("after:I am signal %d\n",signum);
}
int main()
{
	signal(SIGINT,sighandler);
	signal(SIGQUIT,sighandler);
	while(1);
	return 0;
}
