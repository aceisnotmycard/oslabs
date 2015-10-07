#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void endless_printer() {
    while (1) {
        printf("I'm barby girl. Barby plasic. It's fantastic.\n");
    }
}

int main() {
    pthread_t thread;

    pthread_create(&thread, NULL, endless_printer, NULL);

    return EXIT_SUCCESS;
}