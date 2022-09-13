/**
 * General structure of a dining philosopher
 *
 * Alternate between thinking/eating
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include "dp.h"

void *philosopher(void *param)
{
	int *lnumber = (int *)param;
	int number = *lnumber;
	int sleep_time;
	int times_through_loop = 0;

	srandom((unsigned)time(NULL));

	while (times_through_loop < 5) {
		sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);
		thinking(sleep_time);

		pickup_forks(number);

		printf("Philosopher %d is eating\n",number);

		sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);
		eating(sleep_time);

		printf("Philosopher %d is thinking\n",number);
		return_forks(number);
		
		++times_through_loop;
	}
}
