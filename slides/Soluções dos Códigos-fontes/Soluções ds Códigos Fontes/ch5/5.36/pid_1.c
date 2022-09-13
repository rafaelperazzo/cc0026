/**
 * A solution to the pid manager problem.
 *
 * Operating System Concepts
 * Copyright John Wiley & Sons, 2013.
 */

#include "pid.h"
#include <pthread.h>
#include <stdio.h>

/**
 * Aloca o mapa de pids.
 */
int allocate_map(void) 
{
int i;

	for (i = PID_MIN; i <= PID_MAX; i++)
		pid_map[i] = 0;

	last = PID_MIN;

	if (pthread_mutex_init(&mutex,NULL) != 0)
		fprintf(stderr,"Unable to initialize mutex\n");

	return last;
}

/**
 * Aloca um pid
 */
int allocate_pid(void)
{
	int n_loops = 0;

	int next;

	/* acquire the mutex lock */
	if (pthread_mutex_lock(&mutex) != 0)
		fprintf(stderr,"Unable to acquire lock\n");

	if (last == PID_MAX)
		next = PID_MIN;
	else
		next = last + 1;

	/* encontre o próximo pid disponível */
	while ( (n_loops <= (PID_MAX - PID_MIN)) && (pid_map[next] == 1) ) {	
		++n_loops;
		++next;
		if (next > PID_MAX)
			next = PID_MIN;
	}

	if (n_loops == (PID_MAX - PID_MIN) + 1) {
		last = -1;
	}
	else {
		/* encontramos um */
		pid_map[next] = 1;

		last = next;
	}

	if (pthread_mutex_unlock(&mutex) != 0)
		fprintf(stderr,"Unable to release mutex\n");

	return last;
}

/**
 * Libera um pid
 */
void release_pid(int pid)
{
	if (pthread_mutex_lock(&mutex) != 0)
		fprintf(stderr,"Unable to acquire mutex\n");

	pid_map[pid] = 0;

	if (pthread_mutex_unlock(&mutex) != 0)
		fprintf(stderr,"Unable to release mutex\n");
}
