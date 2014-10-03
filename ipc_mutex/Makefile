CC = gcc
CFLAGS = -Wall
OBJS = ipc_mutex.o

ipc_mutex:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ipc_mutex -lpthread

$(OBJS):
	$(CC) $(CFLAGS) -c ipc_mutex.c

clean:
	rm -rf *.o
