#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

pthread_t threads[NUM_THREADS];

void printer(char *strings[]) {
    pthread_t current_thread = pthread_self();
    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_equal(current_thread, threads[i])) {
            printf("%s %s\n", strings[i], strings[i + NUM_THREADS]);
        }
    }
}

int main() {
    int i;

    char *strings[] = {
            "1 string",
            "2 string",
            "3 string",
            "4 string",
            "5 string",
            "6 string",
            "7 string",
            "8 string"
    };

    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, printer, strings) != 0) {
            printf("Cannot create %d thread.\n", i);
            return EXIT_FAILURE;
        }
    }
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Cannot join thread %d.\n", i);
            return EXIT_FAILURE;
        }
    }
    printf("Main thread: I'm leaving!\n");
    return EXIT_SUCCESS;
}