#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void read_move(int fd)
{
    FILE *stream = fdopen(fd, "r");
    char c;
    setvbuf(stream, NULL, _IONBF, BUFSIZ);  
    while ((c = fgetc(stream)) != EOF)
    {
        putchar(c);
    }
    fclose(stream);
}

void write_move(int fd, const char *move)
{
    FILE *stream = fdopen(fd, "w");
    setvbuf(stream, NULL, _IONBF, BUFSIZ);
    fprintf(stream, "%s", move);
    fclose(stream);
}

int main() {
    pid_t pid;
    int wpipe[2];
    int rpipe[2];
    if (pipe(wpipe) || pipe(rpipe))
    {
        fprintf(stderr, "Pipe creation failed.\n");
        return EXIT_FAILURE;
    }
    pid = fork();
    if (pid == 0)
    {
        /* gnuchess process */
        setvbuf(stdin, NULL, _IONBF, BUFSIZ);
        setvbuf(stdout, NULL, _IONBF, BUFSIZ);
        setvbuf(stderr, NULL, _IONBF, BUFSIZ);
        dup2(wpipe[0], STDIN_FILENO);
        dup2(rpipe[1], STDOUT_FILENO);
        dup2(rpipe[1], STDERR_FILENO);
        close(wpipe[0]);
        close(wpipe[1]);
        close(rpipe[0]);
        close(rpipe[1]);
        if (execl("/usr/games/gnuchess", "gnuchess", "-x", NULL) == -1)
        {
            fprintf(stderr, "Exec failed.\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    /* parent process */

    printf("Sending move to GNU Chess... \n");
    close(wpipe[0]); /* Close other end */
    write_move(wpipe[1], "c3\n");   

    printf("Reading response... \n");
    close(rpipe[1]); /* Close other end */
    read_move(rpipe[0]);

    /* clean up */  
    close(wpipe[1]);
    close(rpipe[0]);    

    /* kill gnuchess */
    kill(pid, SIGTERM);

    return EXIT_SUCCESS;
}
