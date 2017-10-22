#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int signin()
{
	int opt;
	printf("             1.登入       2.注册       3.退出\n");
	printf("Please input: ");
	scanf("%d",&opt);
	if(1==opt)return 1;
	else if(2==opt){
		char username[20]={0};
		char *password;
		printf("Please input new username: ");
		scanf("%s",username);
		password=getpass("Please input new password: ");
		printf("%s,%s\n",username,password);
	}else return 3;
}
int main()
{
	int ret;
	while(1)
	{
		ret=signin();
		if(ret==1)break;
		else if(ret==2)continue;
		else return 0;
	}
	printf("Please input username:\n");
	return 0;
}
