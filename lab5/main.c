#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void exit_handler() {
    printf("\nOh, you finally stopped me.\n");
}


void endless_printer() {
    pthread_cleanup_push(exit_handler, NULL);
    while (1) {
        write(STDOUT_FILENO, "Hello\n", 6);
    }
    pthread_cleanup_pop(1);
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