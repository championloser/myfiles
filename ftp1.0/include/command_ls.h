#ifndef __COMMAND_LS_H__
#define __COMMAND_LS_H__
#include"head.h"

char* Trantime(char * oldtime);
char *Tranmode(struct stat *buf,struct dirent *p);
int Printls(char *path,char *name,struct dirent *p,char *combuf);
int command_ls(char *argv,char *combuf);
#endif
