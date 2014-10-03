CC = gcc
CFLAGS = -Wall
OBJS = ipc_semaphore.o

ipc_semaphore:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ipc_semaphore -lpthread

$(OBJS):
	$(CC) $(CFLAGS) -c ipc_semaphore.c

clean:
	rm -rf *.o
