#include"func.h"
int main()
{
	FILE *fp=popen("ls","r");
	char buf[512];
	memset(buf,0,sizeof(buf));
	fread(buf,sizeof(char),512,fp);
	printf("%s",buf);
	return 0;
}
