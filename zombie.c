#include"func.h"
int main()
{
	if(!fork())
	{	
		printf("Child pid=%d,ppid=%d\n",getpid(),getppid());
		return 0;
	}else{
		printf("Parent pid=%d,ppid=%d\n",getpid(),getppid());
		while(1);
	}
}
