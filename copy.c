#include"func.h"
int main()
{
	int begin=time(NULL);
	system("cp tuling.pdf file3.pdf");
	int end=time(NULL);
	printf("time=%d\n",end-begin);
	return 0;
}
