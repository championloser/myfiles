#include"func.h"
int pro_bar1(long len,long totalLen)
{
	double rate=(double)len*100/totalLen;
	printf("Download... %3.0f%c\r",rate,'%');
	fflush(stdout);
	return 0;
}
int pro_bar2(long len,long totalLen)
{
	int rate1=len*100/totalLen;
	char buf[51];
	memset(buf,0,sizeof(buf));
	rate1=rate1/2;
	int i;
	for(i=0;i<rate1;i++)buf[i]='*';
	for(;i<50;i++)buf[i]='-';

	double rate=(double)len*100/totalLen;
	printf("Download... %3.0f%c[%s]\r",rate,'%',buf);
	fflush(stdout);
	return 0;
}
