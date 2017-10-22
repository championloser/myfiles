#include<stdio.h>
#include<unistd.h>
int main()
{
	char buf[256]={0};
	if(NULL==getcwd(buf,sizeof(buf))){perror("getcwd");return -1;}
	puts(buf);
	return 0;
}
