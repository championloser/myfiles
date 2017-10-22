#ifndef __READ_CONF_H__
#define __READ_CONF_H__
#include"head.h"

#define CONFIG "/home/jiaxian/ftp/conf/config"

char* my_strcut(char *buf,char *mode,char end);
int get_addr_port(char **paddr,char **pport,int *pthnum,char **plogfile);
#endif
