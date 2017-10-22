#include"func.h"
int main()
{
	printf("uid=%d,gid=%d,euid=%d,egid=%d\n",getuid(),getgid(),geteuid(),getegid());
	system("chmod 777 jiaxian");
	return 0;
}
