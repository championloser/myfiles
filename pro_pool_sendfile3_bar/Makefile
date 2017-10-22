service.out:service.c
	gcc service.c func.c tcp_listen.c send_recv_fd.c send_recv_n.c pro_bar.c -o service.out
	gcc client.c tcp_connect.c send_recv_n.c pro_bar.c -o client.out
.PHONY:clean
clean:
	rm service.out client.out
