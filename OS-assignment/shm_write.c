#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>


#define BUFFER_SIZE 100
int main(){
    void *shared_memory;
    char buff[100]="";
    int shmid=0;

    //creates a shared memory segment with key 2345,having size 1024 bytes
    //IPC_create is used to create the shared segment if it does not exist
    //0666 are the permissions on the shared segment
    key_t key = (key_t)2345;

    // Create a shared memory segment
    shmid = shmget(key, BUFFER_SIZE, 0666 | IPC_CREAT);
    printf("Key shared memeory is : %d\n",shmid);

    shared_memory=shmat(shmid,NULL,0);//process attached to the shared memory
    printf("Process attached at:%p\n",shared_memory);

    printf("Enter some data to be written to the shared memory\n");
    //get input from the user
    read(0,buff,100);
    strcpy(shared_memory,buff);//data written to the shared memory

    sleep(10);
}