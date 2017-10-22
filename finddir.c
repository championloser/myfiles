#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
void printdir(char *path,int num)
{
	DIR *dir=opendir(path);
	if(NULL==dir){perror("opendir");return;}
	struct dirent *p;
	while((p=readdir(dir))!=NULL)
	{
		if(strcmp(p->d_name,".")!=0 && strcmp(p->d_name,"..")!=0)
		{
			printf("%*s%s\n",num,"",p->d_name);
			if(p->d_type==4)
			{
				char buf[512];
				bzero(buf,sizeof(buf));
				sprintf(buf,"%s%s%s",path,"/",p->d_name);
				printdir(buf,num+4);
			}
		}
	}
}
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return -1;}
	printdir(argv[1],0);
	return 0;
}
