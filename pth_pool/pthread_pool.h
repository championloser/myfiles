#ifndef __PTHREAD_POOL_H__
#define __PTHREAD_POOL_H__
#include"head.h"
#include"tcp.h"
#include"send_recv_file.h"
#include"queue.h"

typedef void* (*Entryfunc)(void *);
typedef struct pthnode{
	Queuepoint que;//等待队列
	pthread_t *arrpthid;//线程ID数组
	int pthnum;	//线程数量
	Entryfunc pthfunc;//线程入口函数
	pthread_cond_t cond;//条件变量
	short startflag;//启动状态
}Pthnode,*Pthnodepoint;

void* pthfunc(void *p);
int Init_pthinfo(Pthnodepoint pthinfo,int pthnum,Entryfunc pthfunc);
#endif
