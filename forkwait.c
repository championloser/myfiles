#include"func.h"
int main()
{
	if(!fork())
	{
		printf("Child pid=%d,ppid=%d\n",getpid(),getppid());
		return 0;
	}else{
		int pid;
		pid=wait(NULL);
		printf("Parent waitpid=%d\n",pid);
		return 0;
	}
}
