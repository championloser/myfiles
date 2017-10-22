#include<stdio.h>
#include<malloc.h>
#include<string.h>
int main()
{
	int n,p=1;
	char *str=(char *)malloc(sizeof(char)*33);
	memset(str,0,sizeof(str));
	printf("Please input a number:");
	scanf("%d",&n);
	int i;
	for(i=31;i>=0;i--)
	{
		if(p&n)str[i]='1';
		else str[i]='0';
		n=n>>1;
	}
	puts(str);
	free(str);
	return 0;
}
