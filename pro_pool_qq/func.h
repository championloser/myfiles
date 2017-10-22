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

#define MAXLINK 10

typedef struct{
	pid_t pid;
	int tfd;
	short busy;
}Node,*Nodepoint;

int tcp_listen(int *sfd,char *ip,char *port);
int tcp_connect(int *sfd,char *ip,char *port);
int create_child(int *sfd,int *epfd,Nodepoint childInfo,int childNum);
int send_fd(int tfd,int *new_fd);
int recv_fd(int tfd,int *new_fd);
int child_work(int new_fd);
