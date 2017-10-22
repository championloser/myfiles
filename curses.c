#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<curses.h>
char* my_getstr()
{
	char *buf=(char*)malloc(sizeof(char)*21);
	memset(buf,0,sizeof(buf));
	int i=0;
	initscr();
	while(buf[i]=getchar(),buf[i]!='\r')
	{
		if(buf[i]!='\b' && i<20){putchar(buf[i]);i++;continue;}
		if(buf[i]=='\b' && i>0 && i<20){printf("\b \b");i--;continue;}
	}
	buf[i]='\n';
	endwin();
	printf("%s",buf);
	return buf;
}
int main()
{
	char *buf;
	buf=my_getstr();
	printf("%s",buf);
	return 0;
}
