service.out:service.c
	gcc service.c process_pool.c tcp.c send_recv_fd.c send_recv_file.c -o service.out
	gcc client.c tcp.c send_recv_file.c -o client.out
.PHONY:clean
clean:
	rm service.out client.out
