#include"func.h"
int main()
{
	if(!fork())
	{
		printf("Child pid=%d,ppid=%d\n",getpid(),getppid());
		return 0;
	}else{
		int pid,status;
		pid=wait(&status);
		printf("wait successed,the pid=%d,status=%d\n",pid,status);
		if(WIFEXITED(status))
		{
			printf("Terminated normally,status=%d\n",WEXITSTATUS(status));
		}else{
			printf("Child crash\n");
		}
		return 0;
	}
}
