#ifndef __QUEUE_H__
#define __QUEUE_H__
#include"head.h"

typedef struct fdnode{
	int fd;
	struct fdnode* next;
}Fdnode,*Fdnodepoint;
typedef struct queue{
	Fdnodepoint head,tail;
	int size;
	int maxsize;
	pthread_mutex_t mutex;
}Queue,*Queuepoint; 

int Init_queue(Queuepoint que,int maxsize);
int Push_queue(Queuepoint que,Fdnodepoint pfdno);
int Pop_queue(Queuepoint que,Fdnodepoint *ppfdno);
#endif
