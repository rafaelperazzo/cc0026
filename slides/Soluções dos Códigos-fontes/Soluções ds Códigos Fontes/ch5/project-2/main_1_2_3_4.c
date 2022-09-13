/**
 * Solution to dining philosophers using POSIX mutexes and condition varaibles.
 *
 * Operating System Concepts - Ninth Edition
 * John Wiley & Sons - 2013.
 */

#include <pthread.h>
#include <stdio.h>
#include "dp.h"

pthread_t tid[NUMBER];

/**
 * Initialize all relevant data structures and
 * synchronization objects.
 */
void init()
{
int i;

	for (i = 0; i < NUMBER; i++) {
		state[i] = THINKING;
		thread_id[i] = i;
		pthread_cond_init(&cond_vars[i],NULL);
	}

	pthread_mutex_init(&mutex_lock, NULL);
}

void create_philosophers()
{
int i;

	for (i = 0; i < NUMBER; i++) {
		pthread_create(&tid[i], 0, philosopher, (void *)&thread_id[i]);
	}
}

int main(void)
{
int i;

	init();

	create_philosophers();

	for (i = 0; i < NUMBER; i++)
		pthread_join(tid[i],NULL);

	return 0;
}
