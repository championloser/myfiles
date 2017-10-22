#include"func.h"
void Recycle(void * str)
{
	free((char*)str);
	printf("I am Recycle,free successful\n");
}
void* pthfunc(void *p)
{
	char *str=(char *)malloc(sizeof(char)*10);
	//pthread_cleanup_push(Recycle,(void*)str);	
	printf("I am child pthread\n");
	//pthread_cleanup_pop(1);
	printf("after pop: I am child pthread\n");
}
int main()
{
	pthread_t pthid;
	pthread_create(&pthid,NULL,pthfunc,NULL);
	int ret=-1;
	printf("before cancel:I am main pthread\n");
	ret=pthread_cancel(pthid);
	printf("I am main pthread,ret=%d\n",ret);
	sleep(5);
	printf("I am main pthread,I am awake\n");
	return 0;
}
