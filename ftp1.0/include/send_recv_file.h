#ifndef __SEND_RECV_FILE_H__
#define __SEND_RECV_FILE_H__
#include"head.h"

#define FILENAME "file"

typedef struct{
	int len;
	char buf[1000];
}Data,*Datapoint;

int pro_bar1(long len,long totalLen);
int pro_bar2(long len,long totalLen);
int send_n(int sfd,const void *buf,int len,int flag);
int recv_n(int sfd,void *buf,int len,int flag);
int send_file(int new_fd,char *filepath,char *filename);
int recv_file(int new_fd,char *filepath);
#endif
