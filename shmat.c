#include"func.h"
int main(int argc,char* argv[])
{
	if(argc!=2){printf("error argc\n");return 1;}
	int shmid=atoi(argv[1]);
	char *p=shmat(shmid,NULL,0);
	printf("%s\n",p);
	return 0;
}
