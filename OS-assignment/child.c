#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p1, p2;
    int y = 0;
    p1 = fork();
    if (p1 > 0)
    {
        wait(NULL);
        y--;
        printf("This is parent. ProcessId = %d, y = %d\n", getpid(), y);
    }
    else if (p1 == 0)
    {
        p2 = fork();
        if (p2 > 0)
            wait(NULL);
        else if (p2 == 0)
        {
            y += 5;
            printf("This is grandchild. ProcessId = %d, Parent Process Id = %d, y = %d\n", getpid(), getppid(), y);
            exit(0);
        }
        y += 1;
        printf("This is child. Process Id = %d, Parent Process Id = %d, y = %d\n", getpid(), getppid(), y);
        exit(0);
    }
    else
    {
        printf("Fork creation failed!\n");
    }
    return 0;
}