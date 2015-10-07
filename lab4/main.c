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
    pthread_create(&thread, NULL, endless_printer, NULL);
    sleep(2);
    pthread_cancel(thread);
    return EXIT_SUCCESS;
}