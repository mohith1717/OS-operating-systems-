// multiply.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("There's a error ");
        exit(EXIT_FAILURE);
    }

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    printf("Child process: x = %d, y = %d\n", x, y);
    printf("Product: %d\n", x * y);

    return 0;
}
