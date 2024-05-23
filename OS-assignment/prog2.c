#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char str[100]; 
    printf("Enter the string:\n");
    scanf("%s",str);
    char buf[1024];

    if (pipe(pipefd) == -1) {
        fprintf(stderr, "pipe failed!1");
        return  1;
    }
    pid = fork();

    if (pid == -1) {
        fprintf(stderr, "fork failed");
        return  1;
    }
    if (pid >  0) { 
        close(pipefd[0]); 
        write(pipefd[1], str, strlen(str));
        close(pipefd[1]);
    } else { 
        close(pipefd[1]); 
        read(pipefd[0], buf, sizeof(buf));
        close(pipefd[0]); 
        int len = strlen(buf);
        for (int i =  0; i < len /  2; i++) {
            char temp = buf[i];
            buf[i] = buf[len - i -  1];
            buf[len - i -  1] = temp;
        }

        printf("Reversed string: %s\n", buf);
    }

    return  0;
}
