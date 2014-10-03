CC = gcc
CFLAGS = -Wall
OBJS = ipc_bidirectional_pipe.o

ipc_bidirectional_pipe:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ipc_bidirectional_pipe -lpthread

$(OBJS):
	$(CC) $(CFLAGS) -c ipc_bidirectional_pipe.c

clean:
	rm -rf *.o
