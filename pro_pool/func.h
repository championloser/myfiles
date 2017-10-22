#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<sys/uio.h>
#include<sys/stat.h>
#include<time.h>

#define MAXLINK 10
#define FILENAME "file"

typedef struct{
	pid_t pid;
	int tfd;
	short busy;
}Node,*Nodepoint;
typedef struct{
	int len;
	char buf[1000];
}Data,*Datapoint;

int tcp_listen(int *sfd,char *ip,char *port);
int tcp_connect(int *sfd,char *ip,char *port);
int create_child(int *sfd,int *epfd,Nodepoint childInfo,int childNum);
int send_fd(int tfd,int *new_fd);
int recv_fd(int tfd,int *new_fd);
int child_work1(int new_fd);
int child_work2(int new_fd);
int child_work3(int new_fd);
int client_work1(int sfd);
int client_work2(int sfd);
int client_work3(int sfd);
int send_n(int sfd,const void *buf,int len,int flag);
int recv_n(int sfd,void *buf,int len,int flag);
int pro_bar1(long len,long totalLen);
int pro_bar2(long len,long totalLen);
int send_file(int new_fd,char *filename);
int recv_file(int new_fd);
