#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_STEPS 20000
#define DEFAULT_NUM_THREADS 2

typedef struct param {
    double local_result;
    int start_pos;
} param;

int num_threads = DEFAULT_NUM_THREADS;

param *calculate_pi(param *p) {
    int i;
    for (i = p->start_pos; i < NUM_STEPS; i += num_threads) {
        p->local_result += 1.0 / (i * 4.0 + 1.0);
        p->local_result -= 1.0 / (i * 4.0 + 3.0);
    }
    return p;
}

int main(int argc, char **argv) {
    switch (argc) {
        case 1:
            printf("Using %d threads \n", DEFAULT_NUM_THREADS);
            break;
        case 2:
            num_threads = atoi(argv[1]);
            if (num_threads < 1) {
                printf("NUM_THREADS should be positive number\n");
                return EXIT_FAILURE;
            }
            break;
        default:
            printf("Usage: calc NUM_THREADS\n");
            return EXIT_FAILURE;
    }

    int i = 0;
    pthread_t *threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t));
    param *params = (param *) malloc(num_threads * sizeof(param));
    double pi = 0.0;

    for (i = 0; i < num_threads; i++) {
        params[i].local_result = 0.0;
        params[i].start_pos = i;
        if (pthread_create(threads + i, NULL, calculate_pi, params + i) != 0) {
            printf("Cannot create thread.\n");
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], (void **) params + i) != 0) {
            printf("Cannot join thread %d\n", i);
            return EXIT_FAILURE;
        } else {
            pi += params[i].local_result;
            printf("pi/4 = %.16lf\n", pi);
        }
    }

    pi *= 4.0;
    printf("pi = %.16lf\n", pi);

    return EXIT_SUCCESS;
}