#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    pid_t proc = fork();

    if (proc < 0)
    {
        printf("Error occured");
        exit(0);
    }
    else if (proc == 0)
    {
        printf("Child process id is %d \n", getpid());
        execlp("ps", "ps", "-u", NULL);
    }
    else
    {
        wait(NULL);
        printf("Parent process ID is %d\n", getpid());
    }
    return 0;
}