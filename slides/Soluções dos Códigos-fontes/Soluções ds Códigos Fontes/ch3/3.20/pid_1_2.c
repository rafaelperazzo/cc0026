/**
 * Uma solução para o problema do gerenciador de pid. 
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

	return last;
}

/**
 * Aloca um pid
 */
int allocate_pid(void)
{
	int n_loops = 0;

	int next;

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
		return -1;
	}
		
	/* encontramos um */
	pid_map[next] = 1;

	last = next;

	return last;
}

/**
 * Libera um pid
 */
void release_pid(int pid)
{
	pid_map[pid] = 0;
}
