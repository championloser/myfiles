#include"pthread_pool.h"
int main(int argc,char *argv[])
{
	if(argc!=1){printf("error argc\n");return 1;}
	char *address;
	char *port;
	int pthnum;
	char *logfile;
	int ret=get_addr_port(&address,&port,&pthnum,&logfile);//从配置信息中获取IP端口和线程数
	if(ret!=0){printf("get configuration information error!\n");return -1;}
	printf("address=%s,port=%s,pthread_num=%d,logfile=%s\n",address,port,pthnum,logfile);
	//close(STDOUT_FILENO);
	//int logfd=open(logfile,O_WRONLY|O_APPEND);
	Pthnode pthinfo;
	Init_pthinfo(&pthinfo,pthnum,pthfunc_ftp);//创建所有线程并初始化信息
	Init_queue(pthinfo.que,MAXLINK);//初始化队列
	int sfd;
	ret=tcp_listen(&sfd,address,port);//监听端口
	if(-1==ret){perror("tcp_listen");return 2;}
	int new_fd;
	struct sockaddr_in cliaddr;
	memset(&cliaddr,0,sizeof(cliaddr));
	int addrlen=sizeof(cliaddr);
	while(1)
	{
		new_fd=accept(sfd,(struct sockaddr*)&cliaddr,&addrlen);
		printf("%s:Main pthread:cilent addr=%s,port=%d\n",cur_time(),inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
		Fdnodepoint pfdno=(Fdnodepoint)malloc(sizeof(Fdnode));
		//上面绝对不能用Fdnode fdno分配栈空间,while循环会重复分配同一块空间给fdno
		memset(pfdno,0,sizeof(Fdnode));
		pfdno->fd=new_fd;
		pthread_mutex_lock(&pthinfo.que->mutex);
		Push_queue(pthinfo.que,pfdno);//让new_fd排队
		pthread_mutex_unlock(&pthinfo.que->mutex);
		printf("%s:I am main pthread,quesize=%d\n",cur_time(),pthinfo.que->size);
		pthread_cond_signal(&pthinfo.cond);//给线程发一个信号
	}
}
