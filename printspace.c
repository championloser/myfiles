#include<stdio.h>
int main()
{
	int num;
	printf("Please input the number of the space:");
	scanf("%d",&num);
	printf("%s\n","space");
	printf("%*s%s\n",num,"","space");
	return 0;
}
