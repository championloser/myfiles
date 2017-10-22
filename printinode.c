#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return -1;}
	DIR *dir=opendir(argv[1]);
	struct dirent *p=readdir(dir);
	printf("d_ino=%ld d_reclen=%d d_type=%d d_mame=%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
	closedir(dir);
	return 0;
}

