#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 100

int main() {
    int fd1;
    char buff[BUFFER_SIZE] = "";

    // FIFO file path
    char myfifo[BUFFER_SIZE] = "/tmp/myfifo";

    // creating a named file(FIFO)
    mkfifo(myfifo, 0666);

    // first open in read only and read
    fd1 = open(myfifo, O_RDONLY);
    read(fd1, buff, BUFFER_SIZE);

    // Print the read string and close
    printf("Information read is: %s\n", buff);

    close(fd1);

    return 0;
}
