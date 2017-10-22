#ifndef __PROCESS_POOL_H__
#define __PROCESS_POOL_H__
#include"head.h"
#include"tcp.h"
#include"send_recv_fd.h"
#include"send_recv_file.h"

typedef struct{
	pid_t pid;
	int tfd;
	short busy;
}Node,*Nodepoint;

int create_child(int *sfd,int *epfd,Nodepoint childInfo,int childNum);
int child_work1(int new_fd);
int child_work2(int new_fd);
int child_work3(int new_fd);
int client_work1(int sfd);
int client_work2(int sfd);
int client_work3(int sfd);
#endif
