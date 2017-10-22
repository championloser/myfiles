#include"func.h"
int send_file(int new_fd,char *filename)
{
	int fd=open(filename,O_RDONLY);
	Data train;
	memset(&train,0,sizeof(train));
	train.len=strlen(filename);
	strcpy(train.buf,filename);
	send_n(new_fd,&train,4+train.len,0);//发送文件名
	memset(&train,0,sizeof(train));
	struct stat fileStat;
	fstat(fd,&fileStat);
	printf("The data size is %ld\n",fileStat.st_size);
	sprintf(train.buf,"%ld",fileStat.st_size);
	train.len=strlen(train.buf);
	send_n(new_fd,&train,4+train.len,0);//发送文件大小
	
	while(memset(&train,0,sizeof(train)),(train.len=read(fd,train.buf,sizeof(train.buf)))>0)
	{
		send_n(new_fd,&train,4+train.len,0);
	}

	memset(&train,0,sizeof(train));
	send_n(new_fd,&train,sizeof(train),0);//发送空包结束

	close(fd);
	return 0;
}
int recv_file(int sfd)
{
	Data train;
	memset(&train,0,sizeof(train));
	recv_n(sfd,&train.len,4,0);
	recv_n(sfd,train.buf,train.len,0);//接收文件名
	int fd=open(train.buf,O_CREAT|O_WRONLY,0666);
	memset(&train,0,sizeof(train));
	recv_n(sfd,&train.len,4,0);
	recv_n(sfd,train.buf,train.len,0);//接收文件长度
	long curLen,totalLen;
	curLen=0;
	totalLen=atol(train.buf);
	printf("The data size is %ld\n",totalLen);//打印文件长度
	time_t t,check;
	time(&t);
	while(recv_n(sfd,&train.len,4,0),train.len>0)
	{
		memset(train.buf,0,sizeof(train.buf));
		recv_n(sfd,train.buf,train.len,0);
		write(fd,train.buf,train.len);
		curLen=curLen+train.len;
		time(&check);
		if(check>=t+1)
		{
			pro_bar2(curLen,totalLen);
			t=check;
		}
	}
	recv_n(sfd,train.buf,sizeof(train.buf),0);//接收空包
	pro_bar2(totalLen,totalLen);
	printf("\n");
	close(fd);
	return 0;
}
