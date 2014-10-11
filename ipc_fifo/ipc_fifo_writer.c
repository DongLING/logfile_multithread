/*
 * process A: create FIFO and write data
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "./ipc_fifo"

int main()
{
    int pipe_fd;
    
	//access() is a function under Linux.
    //if the pipe file do not exist
    if (access(FIFO_NAME, F_OK) == -1)
    {
        //creat FIFO pipe file
        mkfifo(FIFO_NAME, 0777);
    }
    
    //open FIFO pipe file just created by mkfifo() above.
    //this will be blocked until "some one" opens another end point(read-point) of this pipe
    pipe_fd = open(FIFO_NAME, O_WRONLY);
    
    //write data into pipe 
    write(pipe_fd, "Hi, this is a FIFO test dongLING 20140929!", PIPE_BUF);
    
    //close FIFO pipe file descriptor
    close(pipe_fd);
    
    return 0;
}
