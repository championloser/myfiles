#include"func.h"
void* pthfunc(void *p)
{
	long i=(long)p;
	printf("I am child pthread %ld\n",i);
	return p;
}
int main()
{
	pthread_t pthid1,pthid2;
	void *ret1,*ret2;
	pthread_create(&pthid1,NULL,pthfunc,(void*)1);
	pthread_create(&pthid2,NULL,pthfunc,(void*)2);
	pthread_join(pthid1,&ret1);
	pthread_join(pthid2,&ret2);
	printf("I am main pthread,ret=%ld\n",(long)ret1);
	printf("I am main pthread,ret=%ld\n",(long)ret2);
	return 0;
}
