#include"pthread_pool.h"
int main(int argc,char *argv[])
{
	if(argc!=4){printf("error argc\n");return 1;}

	int pthnum=atoi(argv[3]);
	Pthnode pthinfo;
	Init_pthinfo(&pthinfo,pthnum,pthfunc);//创建所有线程并初始化信息

	Init_queue(pthinfo.que,MAXLINK);//初始化队列

	int sfd;
	int ret=tcp_listen(&sfd,argv[1],argv[2]);//监听端口
	if(-1==ret){perror("tcp_listen");return 2;}

	int new_fd;
	struct sockaddr_in cliaddr;
	memset(&cliaddr,0,sizeof(cliaddr));
	int addrlen=sizeof(cliaddr);
	while(1)
	{
		new_fd=accept(sfd,(struct sockaddr*)&cliaddr,&addrlen);
		printf("Main pthread:cilent addr=%s,port=%d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
		Fdnode fdno;
		memset(&fdno,0,sizeof(fdno));
		fdno.fd=new_fd;
		pthread_mutex_lock(&pthinfo.que->mutex);
		Push_queue(pthinfo.que,&fdno);//让new_fd排队
		pthread_mutex_unlock(&pthinfo.que->mutex);
		printf("I am main pthread,quesize=%d\n",pthinfo.que->size);
		pthread_cond_signal(&pthinfo.cond);//给线程发一个信号
	}
}
