#include"func.h"
typedef struct{
	pthread_t pthid1,pthid2;
	int fds[2];
}Node,*Nodepoint;
void* pthfunc1(void *p)
{
	Nodepoint pInfo=(Nodepoint)p;
	pipe(pInfo->fds);
	char buf[8];
	memset(buf,0,sizeof(buf));
	read(pInfo->fds[0],buf,sizeof(buf));
	void *ret;
	pthread_join(pInfo->pthid2,&ret);
	printf("I am pthread1,the pthread2 ret=%ld,the buf=%s\n",(long)ret,buf);
	return (void*)1;
}
void* pthfunc2(void *p)
{
	Nodepoint pInfo=(Nodepoint)p;
	char buf[]="hello";
	write(pInfo->fds[1],buf,strlen(buf));
	printf("I am pthread2\n");
	return (void*)2;
}
int main()
{
	Node Info;
	pthread_create(&Info.pthid1,NULL,pthfunc1,(void*)&Info);
	sleep(1);
	pthread_create(&Info.pthid2,NULL,pthfunc2,(void*)&Info);
	void *ret;
	pthread_join(Info.pthid1,&ret);
	printf("I am main pthread,the pthread1 ret=%ld\n",(long)ret);
	return 0;
}
