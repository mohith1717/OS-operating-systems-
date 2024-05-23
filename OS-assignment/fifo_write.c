#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>  // Include the header file for mkfifo
#include <fcntl.h>

#define BUFFER_SIZE 100

int main() {
    int fd;
    char buff[BUFFER_SIZE] = "";

    // FIFO file path
    char myfifo[BUFFER_SIZE] = "/tmp/myfifo";

    printf("Enter the message to be passed: ");
    read(0, buff, BUFFER_SIZE);

    // creating a named file(FIFO)
    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_WRONLY);

    // write the input to FIFO and close it
    write(fd, buff, strlen(buff) + 1);
    close(fd);

    sleep(10);
    return 0;
}
