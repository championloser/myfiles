#include"read_conf.h"
char* my_strcut(char *buf,char *mode,char end)
//字符截取函数,从buf里返回符合mode匹配后至end字符结尾的一段字符
{
	int i,j,k,l;
	int buflen=strlen(buf);
	buf[buflen]='\n';
	int modelen=strlen(mode);
	char *tmp=(char *)malloc(sizeof(char)*(modelen+1));
	memset(tmp,0,sizeof(tmp));
	for(i=0;i<buflen-modelen;i++)
	{
		for(j=0;j<modelen;j++)
		{tmp[j]=buf[i+j];}
		if(strcmp(tmp,mode)==0)
		{
			for(k=0;buf[i+modelen+k]!='\n';k++){}
			char *tmp2=(char *)malloc(sizeof(char)*(k+1));
			memset(tmp2,0,sizeof(tmp2));
			for(l=0;l<k;l++)tmp2[l]=buf[i+modelen+l];
			return tmp2;
		}
	}
	return NULL;
}
int get_addr_port(char **paddr,char **pport,int *pthnum,char **plogfile)
//从配置文件中获取配置信息
{
	int fd=open(CONFIG,O_RDONLY);
	char buf[1024];
	memset(buf,0,sizeof(buf));
	read(fd,buf,sizeof(buf)-1);
	char *pnum;
	*paddr=my_strcut(buf,"address:",'\n');
	if(NULL==*paddr)return -1;
	*pport=my_strcut(buf,"port:",'\n');
	if(NULL==*pport)return -1;
	*plogfile=my_strcut(buf,"log:",'\n');
	if(NULL==*plogfile)return -1;
	pnum=my_strcut(buf,"pthread_num:",'\n');
	if(NULL==pnum)return -1;
	*pthnum=atoi(pnum);
	return 0;
}
