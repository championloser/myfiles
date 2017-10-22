#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<dirent.h>
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return -1;}
	DIR *dir=opendir(argv[1]);
	struct dirent *p;
	while((p=readdir(dir))!=NULL){printf("%s\n",p->d_name);}
	closedir(dir);
	return 0;
}
