#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	while(1)
	{
		system("ps -elf|grep ./service.out");
		usleep(150000);
	}
	return 0;
}
