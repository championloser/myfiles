#include"my_mysql.h"
int mysql(char *buf1,char *buf2)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server="localhost";
	char *user="root";
	char *password="jiangjiaxian";
	char *database="test1";
	char *query=buf1;

	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("mysql_real_connect error:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("connect successfully\n");
	}
	if(mysql_query(conn,query))
	{
		printf("mysql_query error:%s\n",mysql_error(conn));
	}else{
		printf("query successfully\n");
		res=mysql_use_result(conn);
		if(res)
		{
			int i;
			while((row=mysql_fetch_row(res))!=NULL)
			{
				for(i=0;i<mysql_num_fields(res);i++)printf("%10s ",row[i]);
				printf("\n");
			}
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}
