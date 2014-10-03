CC = gcc
OBJS = ipc_pthread.o

ipc_pthread:$(OBJS)
	$(CC) $(OBJS) -o ipc_pthread -lpthread

$(OBJS):
	$(CC) -c ipc_pthread.c

clean:
	rm -rf *.o
