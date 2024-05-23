#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>


#define MAX 10
#define BUF_SIZE 100

//structure for message queue

struct mesg_buffer
{
    long mesg_type;
    char mesg_text[BUF_SIZE];
}message;
int main(){
    key_t key;
    int msgid;

    //ftok to generate unique key
    key=ftok("progfile",65);

    //mssget creates a message queue and returns identifier
    msgid=msgget(key,0666 | IPC_CREAT);
    message.mesg_type=1;

    printf("Write file: ");
    fgets(message.mesg_text,MAX,stdin);

    //msgnd to send message
    msgsnd(msgid,&message,sizeof(message),0);

    sleep(6);
    return 0;
}