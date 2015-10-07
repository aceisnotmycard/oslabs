#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 4

pthread_t threads[NUM_THREADS];

void printer(char* strings[]) {
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

    char* strings[] = {
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
        //init threads
        pthread_create(&threads[i], NULL, printer, strings);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return EXIT_SUCCESS;
}