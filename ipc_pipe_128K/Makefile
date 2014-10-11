CC = gcc
CFLAGS = -Wall
OBJS = ipc_pipe_128k.o

ipc_pipe_128k:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ipc_pipe_128k -lpthread

$(OBJS):
	$(CC) $(CFLAGS) -c ipc_pipe_128k.c

clean:
	rm -rf *.o
