#include"func.h"
void sighandler(int signum,siginfo_t * siginfo,void *p)
{
	printf("before:I am signal %d\n",signum);
	sleep(3);
	printf("after:I am signal %d\n",signum);
}
int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_sigaction=sighandler;
	act.sa_flags=SA_SIGINFO;
	sigaction(SIGINT,&act,NULL);
	sigaction(SIGQUIT,&act,NULL);
	char buf[128];
	memset(buf,0,sizeof(buf));
	read(STDIN_FILENO,buf,sizeof(buf));
	puts(buf);
	return 0;
}
