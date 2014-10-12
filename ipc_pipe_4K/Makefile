CC = gcc
CFLAGS = -Wall
OBJS = ipc_pipe_4k.o

ipc_pipe_4k:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ipc_pipe_4k -lpthread

$(OBJS):
	$(CC) $(CFLAGS) -c ipc_pipe_4k.c

clean:
	rm -rf *.o
