#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	int pipe_fd[2], pipe_flag;

	pipe_flag = pipe(pipe_fd);
	if(pipe_flag != 0)
	{
		printf("Pipe can not be created!");
		return -1;
	}

	int write_num, read_num;
//	int write_max_size, read_max_szie;
	char write_buffer[] = "Hello dongLING 20141010.";
	char read_buffer[1024];
	pid_t pid = fork(); /* pid - process ID */	
	if(pid > 0) /* Parent process */
	{
//		close(read_pipe);
		int i = 0;
		for(i; i < 162; i++) /* 162 * number of write_buffer =4*1024 => atomic operation */
		{
			write_num = write(pipe_fd[1], write_buffer, sizeof(write_buffer));	
//			printf("%d\n", write_num);
			printf("Time Written to pipe are %d, total %d\n", i+1, (i+1)*sizeof(write_buffer));
		}
//		sleep(10);
//		return 0;
	}
	else if(pid == 0) /* Child process */
			{
//				close(write_pipe);
				read_num = read(pipe_fd[0], read_buffer, sizeof(read_buffer));
				printf("%d\n", read_num);
				printf("Data from is: %s\n", read_buffer);
//				sleep(10);
//				return 0;
			}
			else 
			{				
				printf("Process created is wrong!");
				return -1;
			}

	return 0;
}
