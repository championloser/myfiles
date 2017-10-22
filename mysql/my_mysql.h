#ifndef __MY_MYSQL_H__
#define __MY_MYSQL_H__
#include"head.h"

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "jiangjiaxian"
#define DATABASE "test1"

int my_mysql(char *buf,MYSQL_RES **pres);
#endif
