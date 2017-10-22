#include"func.h"
void* pthfunc(void* p)
{
	while(1)
	{
		printf("I am child pthread\n");
		sleep(2);
	}
}
int main()
{
	pthread_t pthid;
	int ret=pthread_create(&pthid,NULL,pthfunc,NULL);
	printf("pthid=%ld,ret=%d\n",pthid,ret);
	while(1)
	{
		printf("I am main pthread\n");
		sleep(2);
	}
	return 0;
}
