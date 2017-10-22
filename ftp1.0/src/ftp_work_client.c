#include"ftp_work.h"
int print_prompt(int sfd,Command *ptmpcom,char *prompt)
{
	(*ptmpcom).act=5;
	strcpy((*ptmpcom).buf,"pwd");
	(*ptmpcom).len=strlen((*ptmpcom).buf)+8;
	send_n(sfd,ptmpcom,sizeof(struct command),0);
	recv_n(sfd,ptmpcom,sizeof(struct command),0);
	int len=strlen(ptmpcom->buf);
	(ptmpcom->buf)[len-1]='\0';
	printf("%s%s",ptmpcom->buf,prompt);
	fflush(stdout);
	memset(ptmpcom,0,sizeof(struct command));
}
char* create_salt()
{
	char buf[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	srand(time(NULL));
	char tmp[9]={0};
	int i;
	for(i=0;i<8;i++){tmp[i]=buf[rand()%62];}
	char *salt=(char*)calloc(13,sizeof(char));
	sprintf(salt,"$6$%s$",tmp);
	return salt;
}
int signin()
{
	int opt;
	printf("             1.登入       2.注册       3.退出\n");
	printf("Please input: ");
	scanf("%d",&opt);
	if(1==opt)return 1;
	else if(2==opt)
	{
		char username[20]={0};
		char *password;
		printf("Please input new username: ");
		scanf("%s",username);
		password=getpass("Please input new password: ");
		char buf[256]={0};
		sprintf(buf,"insert user_info(username,password) values('%s','%s')",username,crypt(password,create_salt()));
		MYSQL_RES *res;
		int ret=my_mysql(buf,&res);
		if(0==ret)printf("registered successfully\n");
		else printf("'%s' already exist!\nregistered failure!\n",username);
		return 2;
	}
	else return 3;
}
int ftp_work_client(int sfd)
{
	int ret;
	while(1)
	{
		ret=signin();//注册功能
		if(ret==1)break;
		else if(ret==2)continue;
		else return 0;
	}
	char username[20];
	char *password;
	printf("Please input username:");
	scanf("%s",username);
	password=getpass("Please input password:");//获取用户名和密码

	Command com;
	memset(&com,0,sizeof(com));
	com.act=1;
	sprintf(com.buf,"%s",username);
	com.len=8+strlen(com.buf);
	send_n(sfd,&com,sizeof(com),0);//将用户名发送给服务器
	recv_n(sfd,&com,sizeof(com),0);//如果存在此用户,将收到salt值
	if(-1==com.act){printf("'%s' is not exist!\nlogin failure!\n",username);return 0;}
	else{
		char salt[32]={0};
		strcpy(salt,com.buf);
		memset(&com,0,sizeof(com));
		sprintf(com.buf,"%s",crypt(password,salt));
		send_n(sfd,&com,sizeof(com),0);//将密文发送给服务器端
	}
	memset(&com,0,sizeof(com));
	recv_n(sfd,&com,sizeof(com),0);//接收服务器响应
	if(-1==com.act){printf("Login failure:password error!\n");return 0;}
	printf("Login successfully\n");
	Command tmpcom;
	print_prompt(sfd,&tmpcom,"$ ");

	while(memset(&com,0,sizeof(com)),read(STDIN_FILENO,com.buf,sizeof(com.buf)))
	{
		com.buf[strlen(com.buf)-1]='\0';//把末尾\n去掉
		com.len=strlen(com.buf)+8;
		com.act=2;
		send_n(sfd,&com,sizeof(com),0);//把用户输入发送给服务器
		memset(&com,0,sizeof(com));
		recv_n(sfd,&com,sizeof(com),0);//从服务器接收命令结果

		if(-1==com.act){printf("Invalid command!\n");}
		else if(0==com.act){
			printf("%s",com.buf);
		}else if(1==com.act){//act等于1表示服务器要发文件了
			if(-1==recv_file(sfd,"./"))printf("recv_file failure\n");
			else printf("recv_file successfully\n");
		}else if(4==com.act){//act等于4表示服务器要收文件了
		}else if(6==com.act){
			if(!access(com.buf,R_OK))
			{
				char filename[50];
				strcpy(filename,com.buf);
				memset(&com,0,sizeof(com));
				com.act=7;
				send_n(sfd,&com,sizeof(com),0);
				printf("send %s...\n",filename);
				if(-1==send_file(sfd,filename,filename))printf("send_file failure\n");
				else printf("recv_file successfully\n");
			}else{
				memset(&com,0,sizeof(com));
				com.act=8;
				send_n(sfd,&com,sizeof(com),0);
				printf("Invalid command!\n");
			}
		}
		else if(2==com.act)return 0;
		print_prompt(sfd,&tmpcom,"$ ");
	}
	return 0;
}
