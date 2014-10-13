#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define K 1024

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

//    int write_num = 0, read_num = 0;
    char write_buffer[] = "Hello dongLING 20141010.";
    char read_buffer[4*K]; /* <=4KB is only atomic size for write_buffer and read_buffer */

    pid_t pid = fork();		/* pid - process ID */
	/* There are 2 processes: parent process and child process. */

    if(pid > 0) /* Parent process */
	{	
		close(*read_pipe);
		
		int i = 0;
		for(i; i < 162; i++)
			{	/* 162 * number of write_buffer =4*1024 => atomic operation */
			    write(*write_pipe, write_buffer, sizeof(write_buffer));
			    printf("Time Wrote to pipe are: %d, total %d\n", i + 1, (i + 1) * sizeof(write_buffer));
			}

		sleep(7);
    }
	
	else if(pid == 0) /* Child process */
			{	
				close(*write_pipe);

				read(*read_pipe, read_buffer, sizeof(read_buffer)); /* Only one time read pipe! */
				printf("Strings readed from pipe are: %s\n", read_buffer);

				sleep(7);
		    }
			else
				{
					printf("Process created is wrong!");
					return -1;
			    }

    return 0;
}
