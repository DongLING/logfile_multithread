#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define K 2014
#define WRITE_MAX_SIZE (128*K)
#define READ_MAX_SIZE (1*K)
/* Same size for write_buffer and read_buffer is the best! */
/* Data communication is my focus, not others! */

int main()
{
	int pipe_fd[2], pipe_flag;
	int *write_pipe = &pipe_fd[1];
	int *read_pipe = &pipe_fd[0];
// Rename for easier understand 2 operations of pipe.

	pipe_flag = pipe(pipe_fd);
	if(pipe_flag != 0)
	{
		printf("Pipe can not be created!");
		return -1;
	}

	int write_num = 0, read_num = 0;
	char write_buffer[WRITE_MAX_SIZE] = "Hello dongLING 20141010.";
	char read_buffer[READ_MAX_SIZE];

	pid_t pid = fork(); /* pid - process ID */	
	/* There are 2 processes: parent process and child process. */

	if(pid > 0) /* Parent process */
	{
		int write_size = WRITE_MAX_SIZE;

		close(*read_pipe);
		while(write_size > 0)
		{
			write_num = write(*write_pipe, write_buffer, write_size);	
			// return string number wrote = write_num
			if(write_num > 0)
				{
					write_size -= write_num;
					printf("Strings wrote in pipe are: %s\n", write_buffer);
					printf("Write %d bytes data, the rest is: %d bytes\n", write_num, write_size);
				}
				else
				{
					sleep(7);
				}
		}
		printf("Finally strings wrote in pipe are: %s\n", write_buffer);
	}

	else if(pid == 0) /* Child process */
			{
				close(*write_pipe);
				int read_size = READ_MAX_SIZE;
	            read_num = read(*read_pipe, read_buffer, read_size);
	            // return string number wrote = write_num
	            if(read_num > 0)
	                {
	                    read_size -= read_num;
	                    printf("Strings readed from pipe are: %s\n", read_buffer);
	                    printf("Read %d bytes data, the rest is: %d bytes\n", read_num, read_size);
	                }
	                else
	                {
	                    sleep(7);
	                }
	        	printf("Finally strings readed from pipe are: %s\n", read_buffer);
		    }

			else 
				{				
					printf("Process created is wrong!");
					return -1;
				}

	return 0;
}
