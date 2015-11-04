#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define PHILO 5
#define DELAY 30000
#define FOOD 50

pthread_mutex_t forks[PHILO];
pthread_t phils[PHILO];

pthread_mutex_t forks_available_mutex;
pthread_cond_t forks_available_cond;

void *philosopher(void *id);

int food_on_table();

void get_forks(int phil, int left_fork, int right_fork);

void down_forks(int, int);

pthread_mutex_t foodlock;

int main(int argn, char **argv) {
    int i;

    pthread_cond_init(&forks_available_cond, NULL);
    pthread_mutex_init(&forks_available_mutex, NULL);

    pthread_mutex_init(&foodlock, NULL);

    for (i = 0; i < PHILO; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    for (i = 0; i < PHILO; i++)
        pthread_create(&phils[i], NULL, philosopher, (void *) i);
    for (i = 0; i < PHILO; i++)
        pthread_join(phils[i], NULL);
    return 0;
}

void *philosopher(void *num) {
    int id;
    int left_fork, right_fork, f;

    id = (int) num;
    printf("Philosopher %d sitting down to dinner.\n", id);
    right_fork = id;

    if (left_fork == PHILO) {
        left_fork = 0;
    } else {
        left_fork = id + 1;
    }

    while (f = food_on_table()) {

        printf("Philosopher %d: get dish %d.\n", id, f);

        get_forks(id, left_fork, right_fork);

        printf("Philosopher %d: eating.\n", id);
        usleep(DELAY * (FOOD - f + 1));

        down_forks(left_fork, right_fork);
    }
    printf("Philosopher %d is done eating.\n", id);
    return (NULL);
}

int food_on_table() {
    static int food = FOOD;
    int myfood;

    pthread_mutex_lock(&foodlock);
    if (food > 0) {
        food--;
    }
    myfood = food;
    pthread_mutex_unlock(&foodlock);
    return myfood;
}

//void get_fork(int phil, int fork, char* hand) {
//    pthread_mutex_lock(&forks[fork]);
//    printf("Philosopher %d got %d fork in %s hand\n", phil, fork, hand);
//}

void get_forks(int phil, int left_fork, int right_fork) {

    int res;
    pthread_mutex_lock(&forks_available_mutex);
    do {
        if (res = pthread_mutex_trylock(&forks[left_fork])) {
            res = pthread_mutex_trylock(&forks[right_fork]);
            //if we took left fork but right fork is not available, give left fork back
            if (res) {
                pthread_mutex_unlock(&forks[left_fork]);
            }
        }
        // if left fork is not available then wait
        if (res) {
            pthread_cond_wait(&forks_available_cond, &forks_available_mutex);
        }
    } while (res);
    pthread_mutex_unlock(&forks_available_mutex);
}

void down_forks(int left_fork, int right_fork) {
    pthread_mutex_lock(&forks_available_mutex);
    pthread_mutex_unlock(&forks[left_fork]);
    pthread_mutex_unlock(&forks[right_fork]);
    pthread_cond_broadcast(&forks_available_cond);
    pthread_mutex_unlock(&forks_available_mutex);
}
