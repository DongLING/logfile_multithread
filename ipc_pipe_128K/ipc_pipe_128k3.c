#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
 
int main()
{
    int pfd[2];
    int ret = pipe(pfd);
    if (ret != 0) {
        perror("pipe");
        exit(-1);
    }
 
    pid_t pid = fork();
    if (pid == 0) {
        close(pfd[1]);
        char rdbuf[1024];
        read(pfd[0], rdbuf, sizeof(rdbuf));
		printf("%s\n", rdbuf);
        return 0;
    } else if (pid > 0) {
        close(pfd[0]);
        char wrbuf[] = "abcd";
        write(pfd[1], wrbuf, sizeof(wrbuf));
        pid_t cpid = waitpid(-1, NULL, 0);
    } else {
        perror("fork");
    }
    return 0;
}
