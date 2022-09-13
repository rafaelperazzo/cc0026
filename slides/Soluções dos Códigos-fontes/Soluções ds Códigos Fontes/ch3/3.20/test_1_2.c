/**
 * test.c
 *
 * Testa a implementa��o do gerenciador de pid.
 *
 * J� que as solu��es dos alunos ainda n�o est�o abordando a seguran�a de threads, � poss�vel
 * que ocorra uma condi��o de corrida na solu��o.
 *
  * Fundamentos de Sistemas Operacionais, Nona Edi��o
 * John Wiley & Sons, 2013.
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "pid.h"

#define NUM_THREADS 100
#define ITERATIONS	10
#define SLEEP		5

int in_use[PID_MAX + 1];

/**
 * lock mutex usado no acesso a uma estrutura de dados
 * para assegurar que n�o sejam usados pids duplicados.
 */
pthread_mutex_t test_mutex;

void *allocator(void *param)
{
	int i, pid;

	for (i = 0; i < ITERATIONS; i++) {
		/* entra em suspens�o por um per�odo de tempo aleat�rio /
		sleep((int)(random() % SLEEP));

		/* aloca um pid */
		pid = allocate_pid();
		printf("allocated %d\n",pid);

		if (pid == -1)
			printf("No pid available\n");
		else {
			/* indica no mapa in_use que o pid est� sendo usado */
			pthread_mutex_lock(&test_mutex);
			if (in_use[pid] == 1) {
				fprintf(stderr,"***PID ALREADY IN USE****\n");
			}
			else
				in_use[pid] = 1;

			pthread_mutex_unlock(&test_mutex);
		
			/* entra em suspens�o por um per�odo de tempo aleat�rio */
			sleep((int)(random() % SLEEP));

			/* libera o pid */
			release_pid(pid);
			pthread_mutex_lock(&test_mutex);
			in_use[pid] = 0;
			pthread_mutex_unlock(&test_mutex);
			
			printf("released %d\n",pid);
		}
	}
}

int main(void)
{
	int i;
	pthread_t tids[NUM_THREADS];

	for (i = 0; i <= PID_MAX; i++) {
		in_use[i] = 0;
	}

	pthread_mutex_init(&test_mutex, NULL);

	/* allocate the pid map */
	if (allocate_map() == -1)
		return -1;

	srandom((unsigned)time(NULL));

	for (i = 0; i < NUM_THREADS; i++) {
		pthread_create(&tids[i], NULL, allocator, NULL);
	}

	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(tids[i], NULL);

	printf("***DONE***\n");

	return 0;
}
