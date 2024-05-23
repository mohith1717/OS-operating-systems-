// main.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Error occured");
        exit(EXIT_FAILURE);
    }

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    printf("Parent process: x = %d, y = %d\n", x, y);

    // Execute the second program using exec
    execl("./multiply", "multiply", argv[1], argv[2], NULL);

    // If execl fails, print an error message
    perror("execl failed");
    exit(EXIT_FAILURE);
}
