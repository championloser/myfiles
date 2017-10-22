#include"func.h"
void sighandler(int signum)
{
	time_t t;
	time(&t);
	printf("%s\n",ctime(&t));
}
int main()
{
	signal(SIGVTALRM,sighandler);
	struct itimerval value;
	memset(&value,0,sizeof(value));
	value.it_value.tv_sec=5;
	value.it_interval.tv_sec=2;
	setitimer(ITIMER_VIRTUAL,&value,NULL);
	sighandler(0);
	while(1);
	return 0;
}
