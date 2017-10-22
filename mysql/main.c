#include"my_mysql.h"
int main()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	int ret;
	char buf[]="select * from user_info";
	ret=my_mysql(buf,&res);
	if(ret!=0)
	{
		printf("mysql query error\n");return -1;
	}
	int i;
	while((row=mysql_fetch_row(res))!=NULL)
	{
		for(i=0;i<mysql_num_fields(res);i++)
		{
			printf("%10s ",row[i]);
		}
		printf("\n");
	}
	return 0;
}
