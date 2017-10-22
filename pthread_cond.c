#include"func.h"
typedef struct{
	pthread_cond_t cond;
	pthread_mutex_t mutex;
}Node,*Nodepoint;
void* pthfunc(void *p)
{
	Nodepoint con=(Nodepoint)p;
	printf("I am child pthread\n");
	pthread_mutex_lock(&con->mutex);
	pthread_cond_wait(&con->cond,&con->mutex);
	pthread_mutex_unlock(&con->mutex);
	printf("I am child, I am awake\n");
	pthread_exit(NULL);
}
int main()
{
	Node con;
	pthread_cond_init(&con.cond,NULL);
	pthread_mutex_init(&con.mutex,NULL);
	pthread_t pthid;
	pthread_create(&pthid,NULL,pthfunc,(void*)&con);
	printf("I am main pthread\n");
	sleep(1);
	pthread_cond_signal(&con.cond);
	pthread_join(pthid,NULL);
	printf("I am main pthread,join success\n");
	return 0;
}
