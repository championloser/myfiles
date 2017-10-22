#include<stdio.h>
int main()
{
	int count=0;
	int data;
	printf("Please input a number:");
	scanf("%d",&data);
	while(data!=0)
	{
		data=data&(data-1);
		count++;
	}
	printf("The count of 1 is %d\n",count);
	return 0;
}
