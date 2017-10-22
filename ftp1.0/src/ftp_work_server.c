#include"ftp_work.h"
char* cur_time()
{
	time_t t;
	time(&t);
	char *curtime=(char*)calloc(30,sizeof(char));
	strcpy(curtime,ctime(&t));
	curtime[strlen(curtime)-1]='\0';
	return curtime;
}
int cut_command(char *buf,char **pusername,char **ppassword,char flag)
{
	int i=0,j=0;
	while(buf[i]!=flag && buf[i]!='\0'){(*pusername)[i]=buf[i];i++;}
	while(buf[i]==flag){i++;}
	while(buf[i]!=flag && buf[i]!='\0'){(*ppassword)[j]=buf[i];i++;j++;}
	return 0;
	
}
char* get_salt(char *encry_password)
{
	char *salt=(char*)calloc(13,sizeof(char));
	int i;
	for(i=0;i<12;i++)salt[i]=encry_password[i];
	return salt;
}
int compare_password(int new_fd,char *username,char **phomepath)
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	Command com;
	char tmp[]="create table if not exists user_info(user_id smallint unsigned primary key auto_increment,username varchar(20) unique key not null,password varchar(128) not null)";//创建user_info数据表
	int ret=my_mysql(tmp,&res);
	if(-1==ret){printf("%s:pthread %ld:create table user_info failure!\n",cur_time(),syscall(SYS_gettid));return -1;}
	//char buf[]="select username,password,path from user_info";
	char buf[]="select username,password from user_info";
	ret=my_mysql(buf,&res);
	if(ret!=0){printf("%s:pthread %ld:mysql connect failure!\n",cur_time(),syscall(SYS_gettid));return -1;}
	while((row=mysql_fetch_row(res))!=NULL)
	{
		if(strcmp(row[0],username)==0)
		{
			memset(&com,0,sizeof(com));
			com.act=0;
			strcpy(com.buf,get_salt(row[1]));
			send_n(new_fd,&com,sizeof(com),0);//发送盐值
			recv_n(new_fd,&com,sizeof(com),0);//接收密文
			if(strcmp(com.buf,row[1])==0)return 0;//校验密码
			else return -1;
		}
	}
	return -1;
}
int send_command_ls(int new_fd,char *argv)
{
	Command com;
	memset(&com,0,sizeof(com));
	com.act=command_ls(argv,com.buf);
	com.len=strlen(com.buf)+8;
	send_n(new_fd,&com,sizeof(com),0);//将ls结果打包发送给客户端
	return 0;
}
int format_path1(char **path)
{
	int len=strlen(*path);
	if((*path)[len-1]!='/'){(*path)[len]='/';}
}
int ftp_work_server(int new_fd,pthread_mutex_t *cdmutex)
{
	Command com;
	memset(&com,0,sizeof(com));
	recv_n(new_fd,&com,sizeof(com),0);//接收客户端传来的用户名
	char username[20]={0};
	strcpy(username,com.buf);
	int homepathlen=50;
	char *homepath=(char*)calloc(homepathlen,sizeof(char));
	memset(&com,0,sizeof(com));
	com.act=compare_password(new_fd,username,&homepath);//在数据库中比对并获取用户家目录,成功返回0,失败-1
	com.len=8+strlen(com.buf);
	send_n(new_fd,&com,sizeof(com),0);//将比对结果打包发送给客户端
	if(-1==com.act)return 0;
	memset(homepath,0,homepathlen);
	getcwd(homepath,homepathlen);//人为定死ftp家目录在当前文件夹下,不从数据库中获取
	//printf("homepath=%s,len=%ld\n",homepath,strlen(homepath));
	format_path1(&homepath);//格式化家目录,保证以/结尾
	int pwdlen=100;
	char *pwd=(char*)calloc(pwdlen,sizeof(char));
	strcpy(pwd,homepath);
	//printf("pwd=%s,len=%ld\n",pwd,strlen(pwd));
	int newpwdlen=100;
	char *newpwd=(char*)calloc(newpwdlen,sizeof(char));
	int commandlen=20;
	char *command=(char*)calloc(commandlen,sizeof(char));
	int argvlen=20;
	char *argv=(char*)calloc(argvlen,sizeof(char));
	long tid=syscall(SYS_gettid);
	long selftid=pthread_self();
	while(memset(&com,0,sizeof(com)),recv_n(new_fd,&com,sizeof(com),0)==0)
	{
		if(com.act!=5)printf("%s:pthread %ld:command:%s\n",cur_time(),tid,com.buf);//过滤掉获取命令提示符请求命令
		else com.act=2;
		cut_command(com.buf,&command,&argv,' ');//截取命令和参数
		memset(&com,0,sizeof(com));
		if(strlen(command)==0)send_n(new_fd,&com,sizeof(com),0);//如果命令为空,发空包过去
		else if(strcmp(command,"ls")==0)
		{
			if(strlen(argv)==0)send_command_ls(new_fd,pwd);
			else if(argv[0]=='/')send_command_ls(new_fd,argv);//如果传过来的是绝对路径
			else{
				strcpy(newpwd,pwd);
				strcat(newpwd,argv);
				//printf("newpwd=%s,len=%ld\n",newpwd,strlen(newpwd));
				send_command_ls(new_fd,newpwd);
			}
		}else if(strcmp(command,"cd")==0)
		{
			if(strlen(argv)==0)
			{
				strcpy(pwd,homepath);
				send_n(new_fd,&com,sizeof(com),0);
			}else{
				if(argv[0]=='/')
				{
					strcpy(newpwd,argv);
				}else{
					strcpy(newpwd,pwd);
					strcat(newpwd,argv);
				}
				format_path1(&newpwd);//格式化新路径,保证以/结尾
				//printf("newpwd=%s\n",newpwd);
				pthread_mutex_lock(cdmutex);
				if(chdir(newpwd))//如果命令无效,切换回家目录发无效信号给客户端
				{
					chdir(homepath);
					pthread_mutex_unlock(cdmutex);
					com.act=-1;send_n(new_fd,&com,sizeof(com),0);
				}else{
					memset(pwd,0,pwdlen);
					getcwd(pwd,pwdlen);//如果cd成功更新当前路径并切换回家目录
					chdir(homepath);
					pthread_mutex_unlock(cdmutex);
					format_path1(&pwd);
					send_n(new_fd,&com,sizeof(com),0);
				}
			}
		}else if(strcmp(command,"pwd")==0)
		{
			strcpy(com.buf,pwd);
			com.buf[strlen(com.buf)]='\n';
			com.len=strlen(com.buf)+8;
			send_n(new_fd,&com,sizeof(com),0);
		}else if(strcmp(command,"rm")==0)
		{
			if(strlen(argv)==0)
			{
				com.act=-1;send_n(new_fd,&com,sizeof(com),0);
			}else{
				strcpy(newpwd,pwd);
				strcat(newpwd,argv);
				com.act=unlink(newpwd);
				send_n(new_fd,&com,sizeof(com),0);
			}
		}else if(strcmp(command,"gets")==0)
		{
			if(strlen(argv)==0)
			{
				com.act=-1;
				send_n(new_fd,&com,sizeof(com),0);
			}else if(argv[0]=='.' || argv[0]=='/'){
				com.act=-1;
				send_n(new_fd,&com,sizeof(com),0);
			}else{
				strcpy(newpwd,pwd);
				strcat(newpwd,argv);
				if(!access(newpwd,R_OK))//如果文件存在并且可读
				{
					com.act=1;
					send_n(new_fd,&com,sizeof(com),0);
					if(-1==send_file(new_fd,newpwd,argv))
					printf("%s:pthread %ld:send_file failure!\n",cur_time(),tid);
					else printf("%s:pthread %ld:send_file successfully\n",cur_time(),tid);
				}else{
					com.act=-1;
					send_n(new_fd,&com,sizeof(com),0);
				}
			}
		}else if(strcmp(command,"puts")==0)
		{
			if(strlen(argv)==0)
			{
				com.act=-1;
				send_n(new_fd,&com,sizeof(com),0);
			}else if(argv[0]=='.' || argv[0]=='/'){
				com.act=-1;
				send_n(new_fd,&com,sizeof(com),0);
			}else{
				strcpy(com.buf,argv);
				com.act=6;
				send_n(new_fd,&com,sizeof(com),0);
				recv_n(new_fd,&com,sizeof(com),0);
				if(com.act==7)//如果客户端回应文件存在并且可读
				{
					if(-1==recv_file(new_fd,pwd))
					printf("%s:pthread %ld:recv_file failure!\n",cur_time(),tid);
					else printf("%s:pthread %ld:recv_file successfully\n",cur_time(),tid);
				}
			}
		}else if(strcmp(command,"exit")==0)
		{
			com.act=2;
			send_n(new_fd,&com,sizeof(com),0);
			break;
		}else{
			com.act=-1;
			send_n(new_fd,&com,sizeof(com),0);
		}

		memset(newpwd,0,newpwdlen);
		memset(command,0,commandlen);
		memset(argv,0,argvlen);
	}
	return 0;
}
