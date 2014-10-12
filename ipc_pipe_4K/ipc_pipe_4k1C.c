#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define k 1024
#define read_max_size (4*k)
#define write_max_szie (128*K)

int main(void)
{
	int pipe_fd[2], pipe_flag = -1;
	pid_t pid;
	char write_buffer[write_max_size] = "Hello pipe world dongLING 20140926!";
//	char string[write_max_size] = "Hello pipe world dongLING 20140926!";
	char read_buffer[read_max_size];

	memset(read_buffer, '\0', sizeof(read_buffer));
	printf("%d\n",sizeof(read_buffer));

// Rename for easier understand 2 operations of pipe.
	int *write_pipe = &pipe_fd[1];
	int *read_pipe = &pipe_fd[0];

	pipe_flag = pipe(pipe_fd);
	if(-1 == pipe_flag)
	{
		printf("Fail to create pipe\n");
		return -1;
	}	

	pid = fork();
	printf("The pid's value is: %d\n", pid);
	// There are 2 proccess. parent's pid >0 and child's pid = 0

	if(pid == -1)
	{
		printf("Fail to fork\n");
		return -1;
	}

	if(pid > 0)   // parent process
	{
		int write_num = 0;

		write_num = write(*write_pipe, write_buffer, write_max_size);
		// return string number written = write_num
		printf("%d\n", write_num);
		
		printf("Write %d bytes data, the rest is %d bytes", write_num, write_max_size);
		close(*write_pipe);
		sleep(1);
		exit(0);
	}
	else   // child process
	{
		int read_num = 0;
		close(*write_pipe);

		read_num = read(*read_pipe, read_buffer, sizeof(read_buffer));
//		printf("Receive %d bytes data: %s \n", read_num, readbuffer);

		while( read_num > 0);
		{
			printf("Receive %d bytes data: %s \n", read_num, read_buffer);
		
			read_num = read(*read_pipe, read_buffer, sizeof(read_buffer));
		}

		printf("No data to read\n");
		close(*read_pipe);
		sleep(1);
		exit(0);
	}
	exit(0);
//	return 0;
}
