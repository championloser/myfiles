#include"func.h"
void sighandler(int signum,siginfo_t *siginfo,void *p)
{
	printf("before:I am signal %d\n",signum);
	sleep(3);
	sigset_t pend;
	sigpending(&pend);
	if(sigismember(&pend,SIGQUIT))
	{
		printf("the %d signal is pending\n",SIGQUIT);
	}else{
		printf("no signal is pending\n");
	}
	printf("after: I am signal %d\n",signum);
}
int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_sigaction=sighandler;
	act.sa_flags=SA_SIGINFO|SA_NODEFER;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGQUIT);
	sigaction(SIGINT,&act,NULL);
	while(1);
	return 0;
}
