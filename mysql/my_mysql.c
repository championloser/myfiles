#include"my_mysql.h"
int my_mysql(char *buf,MYSQL_RES **pres)
{
	MYSQL *conn;
	MYSQL_ROW row;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,SERVER,USER,PASSWORD,DATABASE,0,NULL,0))
	{
		printf("mysql_real_connect:%s\n",mysql_error(conn));
		return -1;
	}
	if(mysql_query(conn,buf))
	{
		printf("mysql_query:%s\n",mysql_error(conn));
		return -1;
	}
	*pres=mysql_use_result(conn);
	//int i;
	//while((row=mysql_fetch_row(*res))!=NULL)
	//{
	//	for(i=0;i<mysql_num_fields(*res);i++)
	//	{
	//		printf("%10s ",row[i]);
	//	}
	//	printf("\n");
	//}
	return 0;
	mysql_close(conn);
	return 0;
}

