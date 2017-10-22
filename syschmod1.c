#include"func.h"
int main()
{
	printf("uid=%d,gid=%d,euid=%d,egid=%d\n",getuid(),getgid(),geteuid(),getegid());
	system("ps -ax -o ruid -o euid -o suid -o fuid -o pif -o fname");
	return 0;
}
