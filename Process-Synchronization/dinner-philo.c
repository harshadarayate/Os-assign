#include <stdio.h>

#include <pthread.h>

#include <semaphore.h>

#include<unistd.h>   //for sleep function

#define N 5

#define THINKING 0

#define HUNGRY 1

#define EATING 2

#define LEFT (ph_num + 4) % N

#define RIGHT (ph_num + 1) % N



int state[N];

int phil_num[N] = { 0, 1, 2, 3, 4 };

sem_t mutex;

sem_t S[N];



void test(int ph_num)

{

    if (state[ph_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)

    {

        state[ph_num] = EATING;

        printf("Philosopher %d takes fork %d and %d\n", ph_num + 1, LEFT + 1, ph_num + 1);

        printf("Philosopher %d is eating\n", ph_num + 1);

        sem_post(&S[ph_num]);

    }

}



void take_fork(int ph_num)

{

    sem_wait(&mutex);

    state[ph_num] = HUNGRY;

    printf("Philosopher %d is hungry\n", ph_num + 1);

    test(ph_num);

    sem_post(&mutex);

    sem_wait(&S[ph_num]);

    usleep(1000); 

}



void put_fork(int ph_num)

{

    sem_wait(&mutex);

    state[ph_num] = THINKING;

    printf("Philosopher %d is putting fork %d and %d down\n", ph_num + 1, LEFT + 1, ph_num + 1);

    printf("Philosopher %d is thinking\n", ph_num + 1);

    test(LEFT);

    test(RIGHT);

    sem_post(&mutex);

}



void* philosopher(void* num)

{

    while (1)

    {

        int* ph_num = num;

        usleep(2000); 

        take_fork(*ph_num);

        usleep(1000); 

        put_fork(*ph_num);

    }

}



int main()

{

    int i;

    pthread_t thread_id[N];

    sem_init(&mutex, 0, 1);



    for (i = 0; i < N; i++)

    {

        sem_init(&S[i], 0, 0);

    }



    for (i = 0; i < N; i++)

    {

        pthread_create(&thread_id[i], NULL, philosopher, &phil_num[i]);

        printf("Philosopher %d is thinking\n", i + 1);

    }



    for (i = 0; i < N; i++)

    {

        pthread_join(thread_id[i], NULL);

    }



    sem_destroy(&mutex);

    for (i = 0; i < N; i++)

    {

        sem_destroy(&S[i]);

    }



    return 0;

}

//

