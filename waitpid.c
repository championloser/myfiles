#include"func.h"
int main()
{
	int pid=fork();
	if(!pid)
	{
		printf("Child:pid=%d,ppid=%d\n",getpid(),getppid());
		return 0;
	}else{
		printf("Parent:pid=%d,ppid=%d\n",getpid(),getppid());
		int status;
		int ret;
		while(1)
		{
			ret=waitpid(pid,&status,WNOHANG);
			if(ret!=0)break;
		}
		if(WIFEXITED(status))
		{
			printf("Terminated normally,%d\n",WEXITSTATUS(status));
			return 0;
		}else{
			printf("Child crash,%d\n",WEXITSTATUS(status));
			return 0;
		}
	}
}
