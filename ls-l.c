#include"func.h"
char* Trantime(char * oldtime)
{
	int len;
	for(len=0;oldtime[len]!='\n';len++)
	{}
	oldtime[len-8]='\0';
	char *newtime=(char *)malloc(sizeof(char)*20);
	memset(newtime,0,sizeof(newtime));
	strcpy(newtime,oldtime);
	return newtime;
}
char *Tranmode(int oldmode)
{
	char *newmode=(char *)malloc(sizeof(char)*17);
	memset(newmode,0,sizeof(newmode));
	int i;
	for(i=15;i>=0;i--)
	{
		if(oldmode&1)newmode[i]='1';
		else newmode[i]='0';
		oldmode=oldmode>>1;
	}
	newmode[6]='-';
	int j;
	for(i=7,j=0;j<3;i=i+3,j++)
	{
		if(newmode[i]=='1')newmode[i]='r';
		else newmode[i]='-';
		if(newmode[i+1]=='1')newmode[i+1]='w';
		else newmode[i+1]='-';
		if(newmode[i+2]=='1')newmode[i+2]='x';
		else newmode[i+2]='-';
	}
	newmode[16]='\0';
	return newmode;
}
int Printls(char *path,char *name)
{
	struct stat buf;
	memset(&buf,0,sizeof(buf));
	int ret=stat(path,&buf);
	if(-1==ret){perror("stat");return -1;}
	char *newtime=Trantime(ctime(&buf.st_mtime));
	char *newmode=Tranmode(buf.st_mode);
	printf("%s %ld %s %s %ld %s %s\n",newmode+6,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,newtime,name);
	free(newtime);
	free(newmode);
}
int main(int argc,char *argv[])
{
	if(argc!=2){printf("error argc\n");return -1;}
	DIR *dir=opendir(argv[1]);
	struct dirent *p;
	char path[128];
	while((p=readdir(dir))!=NULL)
	{
		if(strcmp(p->d_name,".")!=0 && strcmp(p->d_name,"..")!=0)
		{
			memset(path,0,sizeof(path));
			sprintf(path,"%s%s%s",argv[1],"/",p->d_name);
			Printls(path,p->d_name);
		}
	}
	return 0;
}
