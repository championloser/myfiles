service.out:service.c pthread_pool.c queue.c send_recv_file.c tcp.c
	gcc service.c pthread_pool.c queue.c send_recv_file.c tcp.c -o service.out -pthread
	gcc client.c send_recv_file.c tcp.c -o client.out
.PHONY:clean
clean:
	rm service.out client.out
