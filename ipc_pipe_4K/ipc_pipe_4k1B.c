#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define K 1024
#define WRITELEN (128*K)

int main(void)
{
	int pipe_fd[2], result = -1;
	int nbytes;
	pid_t pid;
	char string[WRITELEN] = "Hello pipe world dongLING 20140926!";
	char readbuffer[10*K];
//	memset(readbuffer, '\0', sizeof(readbuffer));
	printf("%d\n",sizeof(readbuffer));

// Easy to understand 2 operations of pipe.
	int *write_pipe = &pipe_fd[1];
	int *read_pipe = &pipe_fd[0];

	result = pipe(pipe_fd);
	if(-1 == result)
	{
		printf("Fail to create pipe\n");
		return -1;
	}	

	pid = fork();
	printf("The pid's value is: %d\n", pid);

	if(-1 == pid)
	{
		printf("Fail to fork\n");
		return -1;
	}

//	if(0 < pid)   // child process
	if(0 == pid)   // child process
	{
		int write_size = WRITELEN;
		result = 0;

		close(*read_pipe);
		while(write_size >= 0)
		{
			result = write(*write_pipe, string, write_size);
			// return string number written = result
				printf("%d\n", result);
			if(result > 0)
				{
					write_size -= result;
					printf("Write %d bytes data, the rest is %d bytes", result, write_size);
				}
				else
				{
					sleep(10);
				}
			}
		return 0;
	}
	else   // parent process
	{
		close(*write_pipe);
		while(1);
		{
			nbytes = read(*read_pipe, readbuffer, sizeof(readbuffer));
//			printf("Receive %d bytes data: %s \n", nbytes, readbuffer);
			if(nbytes <= 0)
			{
				printf("No data to write\n");
//				return 1;
				exit(1);
//				break;   // original statement
			}
			printf("Receive %d bytes data: %s \n", nbytes, readbuffer);
		}
	}
	return 0;
}
