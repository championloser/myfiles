#ifndef __FTP_WORK_H__
#define __FTP_WORK_H__
#include"head.h"
#include"my_mysql.h"
#include"command_ls.h"
#include"send_recv_file.h"

typedef struct command{
	int len;
	int act;
	char buf[10000];
}Command,*Commandpoint;

char* cur_time();
int print_prompt(int sfd,Command *ptmpcom,char *prompt);
int cut_command(char *buf,char **pusername,char **ppassword,char flag);
char* get_salt(char *encry_password);
int compare_password(int new_fd,char *username,char **phomepath);
int format_path1(char **path);
int ftp_work_server(int new_fd,pthread_mutex_t *cdmutex);
int ftp_work_client(int sfd);
#endif
