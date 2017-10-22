service.out:service.c
	gcc service.c func.c tcp_listen.c send_recv_fd.c -o service.out
	gcc client.c tcp_connect.c -o client.out
.PHONY:clean
clean:
	rm service.out client.out
