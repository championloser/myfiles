#include"queue.h"
int Init_queue(Queuepoint que,int maxsize)
{
	que->head=NULL;
	que->tail=NULL;
	que->size=0;
	que->maxsize=maxsize;
	pthread_mutex_init(&(que->mutex),NULL);
	return 0;
}
int Push_queue(Queuepoint que,Fdnodepoint pfdno)
{
	if(NULL==que->head)
	{
		que->head=pfdno;
		que->tail=pfdno;
	}else{
		que->tail->next=pfdno;
		que->tail=pfdno;
	}
	que->size++;
}
int Pop_queue(Queuepoint que,Fdnodepoint *ppfdno)
{
	*ppfdno=que->head;
	que->head=que->head->next;
	if(NULL==que->head)que->tail=NULL;
	que->size--;
}
