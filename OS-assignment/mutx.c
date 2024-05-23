#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>


pthread_mutex_t lock;
int counter=0;

void *thread_function(void *ard){
    pthread_mutex_lock(&lock);

    unsigned long i=0;

    counter+=1;
    printf("\n Jon %d has started",counter);

    for(int i=0;i<0xFFFFFFFF;i++);

    printf("\n Jon %d has started",counter);
    pthread_mutex_lock(&lock);
    return NULL;
}

int main(){

    int i=0;
    int error;
    if(pthread_mutex_lock(&lock,NULL)!=0){
        
    }
}
