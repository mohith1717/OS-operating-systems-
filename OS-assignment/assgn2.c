#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void sorti(int *arr, int len)
{
    int min = 0;
    int temp = 0;
    for (int i = 0; i < len - 1; i++)
    {
        min = arr[i];
        if (min > arr[i + 1])
        {
            temp = min;
            min = arr[i + 1];
            arr[i + 1] = temp;
        }
    }
}
void printarray(int *arrayy)
{
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", arrayy[i]);
    }
}
int main()
{
    int arr[8] = {1, 6, 2, 4, 5, 8, 9, 0};
    pid_t proc = fork();
    if (proc < 0)
    {
        printf("Error occured \n");
        exit(0);
    }

    else if (proc == 0)
    {
        printf("Inside child process with ID : %d\n ", getpid());
        sorti(&arr, 8);
        printarray(&arr);
    }

    else
    {
        wait(NULL);
        printf("The array is as follows \n");
        printarray(&arr);
    }

    return 0;
}
