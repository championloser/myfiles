#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=3){printf("error argc\n");return 1;}
	if(strcmp(argv[1],"ls")==0)
	{
		DIR *dir=opendir(argv[2]);
		struct dirent *p;
		while((p=readdir(dir))!=NULL)
		{
			printf("%s ",p->d_name);
		}
		printf("\n");
		closedir(dir);
	}
	return 0;
}
