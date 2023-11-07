#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char *argv[])
{
    pid_t pid;
    int fd[2];
    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Pipe Creation Failed");
        return 1;
    }
    pid = fork();
    
    if (pid < 0)
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    if (pid > 0)
    {
        /* Reading the commands 1/sec and writing them in the pipe */
        close(fd[0]);
        for(int i = 1; i < argc; i++) 
        {
            char command = argv[i];
            write(fd[1], command, strlen(command) + 1);
        }
        close(fd[1]);
    }
    else
    {
        /* Process manager process */
        close(fd[1]);
        /* Keep Reading */
        close(fd[0]);
    }
    return 0;
}