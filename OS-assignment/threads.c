#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1
int main(){
    char write_msg[BUFFER_SIZE]="Greetings";
    char read_msg[BUFFER_SIZE]="";
    int fd[2];
    pid_t pid;

    //Create a pipe
    if(pipe(fd)==-1){
        printf("Pipe failed");
        return 1;
    }
    //fork a child process
    pid=fork();
    if(pid>0){
        //close the unused end of the pipe
        close(fd[READ_END]);
        //write to the pipe
        write(fd[WRITE_END],write_msg,strlen(write_msg)-1);
        //close the write end of the pipe
        close(fd[WRITE_END]);
    }
    else if(pid==0){
        //close the unused end of the pipe
        close(fd[WRITE_END]);
        //read from the pipe
        read(fd[READ_END],read_msg,BUFFER_SIZE);
        printf("child process read is %s\n",read_msg);
        //close the write end of the pipe
        close(fd[READ_END]);
    }
    else{
        printf("fork failed");
        return 1;
    }

    return 0;
}