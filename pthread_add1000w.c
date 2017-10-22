#include"func.h"
#define N 10000000
typedef struct{
	int sum;
	pthread_mutex_t mutex;
}Node,*Nodepoint;
void* pthfunc(void *p)
{
	Nodepoint buf=(Nodepoint)p;
	int i;
	for(i=0;i<N;i++)
	{
		pthread_mutex_lock(&buf->mutex);
		buf->sum++;
		pthread_mutex_unlock(&buf->mutex);
	}
	pthread_exit(NULL);
}
int main()
{
	Node buf;
	pthread_mutex_init(&buf.mutex,NULL);
	buf.sum=0;
	pthread_t pthid;
	pthread_create(&pthid,NULL,pthfunc,(void *)&buf);
	int i;
	for(i=0;i<N;i++)
	{
		pthread_mutex_lock(&buf.mutex);
		buf.sum++;
		pthread_mutex_unlock(&buf.mutex);
	}
	pthread_join(pthid,NULL);
	printf("sum=%d\n",buf.sum);
	return 0;
}
