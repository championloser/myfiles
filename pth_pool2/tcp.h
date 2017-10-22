#ifndef __TCP_H__
#define __TCP_H__
#include"head.h"

#define MAXLINK 20

int tcp_listen(int *sfd,char *ip,char *port);
int tcp_connect(int *sfd,char *ip,char *port);
#endif
