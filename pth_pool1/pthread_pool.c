#include"pthread_pool.h"
void* pthfunc(void* p)
{
	Pthnodepoint pthinfo=(Pthnodepoint)p;
	Fdnodepoint pfdno;
	int ret;
	while(1)
	{
		pthread_mutex_lock(&pthinfo->que->mutex);
		if(0==pthinfo->que->size)
		{
			pthread_cond_wait(&pthinfo->cond,&pthinfo->que->mutex);
		}
		Pop_queue(pthinfo->que,&pfdno);
		pthread_mutex_unlock(&pthinfo->que->mutex);
		printf("I am pthread %ld,%ld,I am busy\n",syscall(SYS_gettid),pthread_self());//syscall(SYS_gettid);
		ret=send_file(pfdno->fd,FILENAME);//发文件
		if(0==ret)
		{
			printf("I am pthread %ld,sendding successfully\n",syscall(SYS_gettid));
		}else{
			printf("I am pthread %ld,sendding unsuccessfully\n",syscall(SYS_gettid));
		}
		free(pfdno);
		//free(pfdno);如果主函数while循环中给fdno分配了栈空间,则循环末尾已经free,无需再次free
	}
	//while(1)
	//{
	//	pthread_mutex_lock(&pthinfo->que->mutex);
	//	pthread_cond_wait(&pthinfo->cond,&pthinfo->que->mutex);
	//	printf("I am pthread %ld,%ld,I am busy\n",syscall(SYS_gettid),pthread_self());//syscall(SYS_gettid);
	//	while(pthinfo->que->size>0)
	//	{
	//		Pop_queue(pthinfo->que,&pfdno);
	//		pthread_mutex_unlock(&pthinfo->que->mutex);
	//		printf("I am pthread %ld,I am sendding file\n",syscall(SYS_gettid));
	//		send_file(pfdno->fd,FILENAME);//发文件
	//		printf("I am pthread %ld,sendding successful\n",syscall(SYS_gettid));
	//		//free(pfdno);                                 //主函数while循环中已经free,无需再次free
	//		printf("I am pthread %ld,free successful\n",syscall(SYS_gettid));
	//		pthread_mutex_lock(&pthinfo->que->mutex);
	//	}
	//	pthread_mutex_unlock(&pthinfo->que->mutex);
	//}
}
int Init_pthinfo(Pthnodepoint pthinfo,int pthnum,Entryfunc pthfunc)
{
	pthinfo->que=(Queuepoint)calloc(1,sizeof(Queue));
	pthinfo->arrpthid=(pthread_t*)calloc(pthnum,sizeof(pthread_t));
	pthinfo->pthnum=pthnum;
	pthinfo->pthfunc=pthfunc;
	pthread_cond_init(&pthinfo->cond,NULL);

	int i;
	pthread_t pthid;
	for(i=0;i<pthnum;i++)
	{
		pthread_create(&pthid,NULL,pthfunc,(void *)pthinfo);
		pthinfo->arrpthid[i]=pthid;
	}
	pthinfo->startflag=1;//启动状态设置为1
	for(i=0;i<pthnum;i++)
	{
		printf("I am pthread %ld\n",pthinfo->arrpthid[i]);
	}
	return 0;
}
