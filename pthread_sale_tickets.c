#include"func.h"
typedef struct{
	int sum;
	pthread_mutex_t mutex;
}Ticket,*Ticketpoint;
void* pthfunc1(void *p)
{
	Ticketpoint ptic=(Ticketpoint)p;
	while(1)
	{
		pthread_mutex_lock(&ptic->mutex);
		if(ptic->sum>0)
		{
			printf("I am salewindow1,sum=%d\n",ptic->sum);
			sleep(2);
			ptic->sum--;
			printf("I am salewindow1,sale successful,sum=%d\n",ptic->sum);
			pthread_mutex_unlock(&ptic->mutex);
		}else{
			pthread_mutex_unlock(&ptic->mutex);
			printf("The ticket is over,salewindow1 closed\n");
			break;
		}
	}
	pthread_exit(NULL);
}
void* pthfunc2(void *p)
{
	Ticketpoint ptic=(Ticketpoint)p;
	while(1)
	{
		pthread_mutex_lock(&ptic->mutex);
		if(ptic->sum>0)
		{
			printf("I am salewindow2,sum=%d\n",ptic->sum);
			sleep(2);
			ptic->sum--;
			printf("I am salewindow2,sale successful,sum=%d\n",ptic->sum);
			pthread_mutex_unlock(&ptic->mutex);
		}else{
			pthread_mutex_unlock(&ptic->mutex);
			printf("The ticket is over,salewindow2 closed\n");
			break;
		}
	}
	pthread_exit(NULL);
}
int main()
{
	Ticket tic;
	tic.sum=20;
	pthread_mutex_init(&tic.mutex,NULL);
	pthread_t pthid1,pthid2;
	pthread_create(&pthid1,NULL,pthfunc1,(void*)&tic);
	pthread_create(&pthid2,NULL,pthfunc2,(void*)&tic);
	pthread_join(pthid1,NULL);
	pthread_join(pthid2,NULL);
	return 0;
}
