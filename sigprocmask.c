#include"func.h"
void sighandler(int signum)
{
	printf("before:I am signal %d\n",signum);
	sleep(2);
	printf("after: I am signal %d\n",signum);
}
int main()
{
	sigset_t set,pend;
	sigemptyset(&set);
	sigemptyset(&pend);
	sigaddset(&set,SIGQUIT);
	signal(SIGINT,sighandler);
	sigprocmask(SIG_BLOCK,&set,NULL);
	sleep(5);
	sigpending(&set);
	if(sigismember(&set,SIGQUIT))
	{
		printf("The signal %d is pending\n",SIGQUIT);
	}else{
		printf("There is no signal pending\n");
	}
	sigprocmask(SIG_UNBLOCK,&set,NULL);
	printf("jiangjiaxian\n");
	return 0;
}
