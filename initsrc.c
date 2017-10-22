#include<stdio.h>
#include<curses.h>
char* my_getstr(char *prompt)//从标准输入获取字符串,支持退格修改
{
	printf("%s",prompt);
	char *buf=(char*)malloc(sizeof(char)*22);
	memset(buf,0,sizeof(buf));
	int i=0;
	initscr();
	cbreak();
	noecho();
	while(buf[i]=getchar(),buf[i]!='\r')
	{
		if(buf[i]!='\b' && i<20){putchar(buf[i]);i++;continue;}
		if(buf[i]=='\b' && i>0 && i<21){printf("\b \b");i--;continue;}
	}
	buf[i]='\n';
	endwin();
	printf("%s%s",prompt,buf);
	return buf;
}
char* my_getpasswd(char *prompt)//从标准输入获取密码,支持隐藏输入
{
	printf("%s",prompt);
	char *buf=(char*)malloc(sizeof(char)*22);
	memset(buf,0,sizeof(buf));
	int i=0;
	initscr();
	cbreak();
	noecho();
	while(buf[i]=getchar(),buf[i]!='\r')
	{
		if(buf[i]!='\b' && i<20){putchar('*');i++;continue;}
		if(buf[i]=='\b' && i>0 && i<21){printf("\b \b");i--;continue;}
	}
	buf[i]='\n';
	nocbreak();
	endwin();
	printf("%s",prompt);
	for(i=0;i<strlen(buf)-1;i++)putchar('*');
	printf("\n");
	return buf;
}
