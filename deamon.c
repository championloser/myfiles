#include"func.h"
int main()
{
	int pid=fork();
	if(!pid)
	{
		setsid();
		chdir("/");
		umask(0);
		close(STDIN_FILENO);
		close(STDERR_FILENO);
		while(1)
		{
			write(STDOUT_FILENO,"hello\n",6);
			sleep(10);
		}
	}else{
		return 0;
	}
}
