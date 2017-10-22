#include"func.h"
int main()
{
	int fds[2];
	pipe(fds);
	if(!fork())
	{
		close(fds[1]);
		char buf[128];
		memset(buf,0,sizeof(buf));
		read(fds[0],buf,sizeof(buf));
		printf("Child:%s\n",buf);
		return 0;
	}else{
		close(fds[0]);
		write(fds[1],"hello world",11);
		wait(NULL);
		return 0;
	}
}
