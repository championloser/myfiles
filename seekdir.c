#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
int main(int argc,char *argv[])
{
	if(argc!=3){printf("error argc\n");return -1;}
	DIR *dir=opendir(argv[1]);
	struct dirent *p;
	off_t pos;
	while((p=readdir(dir))!=NULL)
	{
		printf("%s\n",p->d_name);
		if(0==strcmp(p->d_name,argv[2]))
		{
			pos=telldir(dir);
		}
	}
	seekdir(dir,pos);
	p=readdir(dir);
	printf("%s\n",p->d_name);
	closedir(dir);
	return 0;
}
