#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define read_max_size 4096
#define write_max_size 4096*127

int main(int argc, char **argv)
{
    int pipe_fd[2];
    pid_t pid;
    char r_buf[read_max_size];
    char w_buf[write_max_size];
    int writenum;
    int readnum;
    int readsum;
    int ret;

    ret = pipe(pipe_fd);
    if (ret < 0)
	{
		perror("pipe");
		return -1;
    }

    pid = fork();
    if (pid == 0)		// child 
    {
		close(pipe_fd[1]);
		readsum = 0;
		readnum = read(pipe_fd[0], r_buf, read_max_size);
		while (readnum > 0)
		{
		    readsum += readnum;
		    printf("Child: read %d bytes from pipe, sum=%d.\n", readnum, readsum);
		    readnum = read(pipe_fd[0], r_buf, read_max_size);
	}
	
	printf("Child: no more bytes to read from pipe!\n");
	close(pipe_fd[0]);
	sleep(1);
	exit(0);
    }
	else if (pid > 0)		// parent {close(pipe_fd[0]); 
		{writenum = write(pipe_fd[1], w_buf, write_max_size);	// 写操作会阻塞，直到所有数据写完 
	    printf("Parent: write %d bytes to pipe.\n", writenum);
	    close(pipe_fd[1]);
	    sleep(1);
	    exit(0);
		}

	else
	{
		perror("fork");
	    exit(1);
	}

	exit(0);
}

/*
 * 结论：对于阻塞式的pipe，当写入的数据量较大时，并不是以原子性方式写入，而是分多次写入。
 * pipe的缓冲区是65536字节，这个是无法修改的。 
 * 另外，在FIFO中经常提到的一个PIPE_BUF(Linux: 4096bytes)，它仅是保证原子性写入的一个限制，
 * 并不是pipe的capacity。
 * 相关知识 可以参考：pipe(7) 
*/
