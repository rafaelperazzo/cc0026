/**
 * test.c
 *
 * Testa a implementação do gerenciador de pid.
 *
 * Já que as soluções dos alunos ainda não abordam a segurança de threads, é possível
 * que ocorra uma condição de corrida na solução.
 *
 * Fornecemos a segurança de threads para o acesso ao array in_use usando
 * locks mutex. Não esperamos que os alunos usem esses locks até 
 * o material ser abordado no capítulo 5 (Sincronização de Processos.)
 *
 * Operating System Concepts, Ninth Edition
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
 * lock mutex usado no acesso à estrutura de dados
 * para assegurar que não haja pids duplicados em uso.
 */
pthread_mutex_t test_mutex;

void *allocator(void *param)
{
	int i, pid;

	for (i = 0; i < ITERATIONS; i++) {
		/* entra em suspensão por um período de tempo aleatório */
		sleep((int)(random() % SLEEP));

		/* aloca um pid */
		pid = allocate_pid();
		printf("allocated %d\n",pid);

		if (pid == -1)
			printf("No pid available\n");
		else {
			/* indica no mapa in_use que o pid está sendo usado */
			pthread_mutex_lock(&test_mutex);
			if (in_use[pid] == 1) {
				fprintf(stderr,"***PID ALREADY IN USE****\n");
			}
			else
				in_use[pid] = 1;

			pthread_mutex_unlock(&test_mutex);
		
			/* entra em suspensão por um período de tempo aleatório */
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
