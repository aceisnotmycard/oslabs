#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void endless_printer() {
    while (1) {
        write(STDOUT_FILENO, "Hello\n", 6);
    }
}

int main() {
    pthread_t thread;
    if (pthread_create(&thread, NULL, endless_printer, NULL) != 0) {
        printf("Cannot create thread\n");
        return EXIT_FAILURE;
    }
    sleep(2);
    if (pthread_cancel(thread)) {
        printf("Thread not found.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}