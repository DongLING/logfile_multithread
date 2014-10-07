CC = gcc
CFLAGS = -Wall
OBJS = ipc_fifo_128k2.o

ipc_fifo_128k2:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ipc_fifo_128k2 -lpthread

$(OBJS):
	$(CC) $(CFLAGS) -c ipc_fifo_128k2.c

clean:
	rm -rf *.o
