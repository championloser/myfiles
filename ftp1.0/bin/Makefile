service.out:../src/service.c ../src/pthread_pool.c ../src/queue.c ../src/send_recv_file.c ../src/tcp.c
	gcc ../src/service.c ../src/pthread_pool.c ../src/queue.c ../src/send_recv_file.c ../src/tcp.c ../src/ftp_work_server.c ../src/read_conf.c ../src/my_mysql.c ../src/command_ls.c -o service.out -pthread -lmysqlclient -I../include
	gcc ../src/client.c ../src/send_recv_file.c ../src/tcp.c ../src/ftp_work_client.c ../src/read_conf.c ../src/my_mysql.c -o client.out -lmysqlclient -lcrypt -I../include
.PHONY:clean
clean:
	rm service.out client.out
