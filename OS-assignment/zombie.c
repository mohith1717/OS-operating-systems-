#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid = fork();
    if (pid > 0)
    {
        printf("In parent process Id = %d\n", getpid());
        sleep(10);
    }
    else if (pid == 0)
    {
        exit(0);
        printf("In child process. Process Id = %d, parent process Id = %d\n", getpid(), getppid());
    }
    return 0;
}