#ifndef __SEND_RECV_FD_H__
#define __SEND_RECV_FD_H__
#include"head.h"

int send_fd(int tfd,int *new_fd);
int recv_fd(int tfd,int *new_fd);
#endif
