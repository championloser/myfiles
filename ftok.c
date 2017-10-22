#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return 1;}
	key_t key1=ftok(argv[1],0);
	key_t key2=ftok(argv[1],1);
	printf("key1=%d,key2=%d\n",key1,key2);
	return 0;
}
