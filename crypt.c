#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<shadow.h>
#include<crypt.h>
#define _XOPEN_SOURCE
int get_salt(char *salt,char *password)
{
	int i;
	for(i=0;i<12;i++)salt[i]=password[i];
	return 0;
}
int main(int argc,char *argv[])
{
	if(argc!=3){printf("argc error\n");return 0;}
	struct spwd *sp;
	if((sp=getspnam(argv[1]))==NULL){perror("getspnam error");return 0;}
	printf("%s\n",sp->sp_pwdp);
	char salt[64];
	memset(salt,0,sizeof(salt));
	get_salt(salt,sp->sp_pwdp);
	printf("%s\n",salt);
	printf("%s\n",crypt(argv[2],salt));
	return 0;
}
