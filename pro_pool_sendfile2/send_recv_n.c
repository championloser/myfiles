#include"func.h"
int send_n(int sfd,const void *buf,int len,int flag)
{
	int ret=0;
	while(ret<len)
	{
		ret=ret+send(sfd,buf+ret,len-ret,0);
	}
	return 0;
}
int recv_n(int sfd,void *buf,int len,int flag)
{
	int ret=0;
	while(ret<len)
	{
		ret=ret+recv(sfd,buf+ret,len-ret,0);
	}
	return 0;
}
