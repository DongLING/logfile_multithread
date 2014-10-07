#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define K 1024
#define WRITELEN (128*K)

int main(void)
{
	int result = -1;
	int fd[2], nbytes;
	pid_t pid;
	char string[WRITELEN] = "Hello pipe world dongLING 20140926!";
	char readbuffer[10*K];
//	memset(readbuffer, '\0', sizeof(readbuffer));
	printf("%d\n",sizeof(readbuffer));

	int *write_fd = &fd[1];
	int *read_fd = &fd[0];

	result = pipe(fd);
	if(-1 == result)
	{
		printf("fail to create pipe\n");
		return -1;
	}	

	pid = fork();
	printf("The pid's value is: %d\n", pid);

	if(-1 == pid)
	{
		printf("fail to fork\n");
		return -1;
	}

	if(0 == pid)
	{
		int write_size = WRITELEN;
		result = 0;
		close(*read_fd);
		while(write_size >= 0)
		{
			result = write(*write_fd, string, write_size);
				printf("%d\n", result);
			if(result > 0)
				{
					write_size -= result;
					printf("write %d bytes data, the rest is %d bytes", result, write_size);
				}
				else
				{
					sleep(10);
				}
			}
		return 0;
	}
	else
	{
		close(*write_fd);
		while(1);
		{
			nbytes = read(*read_fd, readbuffer, sizeof(readbuffer));
//			printf("Receive %d bytes data: %s \n", nbytes, readbuffer);
			if(nbytes <= 0)
			{
				printf("no data to write\n");
//				return 1;
				exit(1);
//				break;   // original statement
			}
			printf("Receive %d bytes data: %s \n", nbytes, readbuffer);
		}
	}
	return 0;
}
