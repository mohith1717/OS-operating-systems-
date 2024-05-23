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
    
    //msgrcv to recieve message
    msgrcv(msgid,&message,sizeof(message),1,0);

    //display message
    printf("Message recieved : %s\n",message.mesg_text);

    //destroy the message queue

    msgctl(msgid,IPC_RMID,NULL);
    return 0;
}