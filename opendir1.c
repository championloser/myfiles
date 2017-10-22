#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return -1;}
	DIR *dir=opendir(argv[1]);
	if(NULL==dir){perror("opendir");return -1;}
	struct dirent *p=readdir(dir);
	if(NULL==p){perror("readdir");return -1;}
	while(NULL!=p)
	{
		printf("%s ",p->d_name);
		p=readdir(dir);
	}
	printf("\n");
	closedir(dir);
	return 0;
}
