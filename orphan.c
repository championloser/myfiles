#include"func.h"
int main()
{
	if(!fork())
	{
		sleep(2);
		printf("Child uid=%d,gid=%d,euid=%d,egid=%d\n",getuid(),getgid(),geteuid(),getegid());
		while(1);
		return 0;
	}else{
		printf("Parent uid=%d,gid=%d,euid=%d,egid=%d\n",getuid(),getgid(),geteuid(),getegid());
		return 0;
	}
}
