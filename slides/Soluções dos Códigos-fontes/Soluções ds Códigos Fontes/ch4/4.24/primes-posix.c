/**
 * Solu��o do Pthreads para o exerc�cio 4.24
 *
 * Compila��o:
 *  gcc -lpthread primes-posix.c
 *
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <pthread.h>
#include <stdio.h>

/** s� permitiremos at� 256 n�meros primos */
#define MAX_SIZE 256

int primes[MAX_SIZE];

void *runner(void *param); /* o thread */

int main(int argc, char *argv[])
{
int i;
pthread_t tid; /* identificador do thread */
pthread_attr_t attr; /* configura��o de atributos do thread */

if (argc != 2) {
	fprintf(stderr,"usage: a.out <integer value>\n");
	return -1;
}

if (atoi(argv[1]) < 2) {
	fprintf(stderr,"Argument %d must be >= 2 \n",atoi(argv[1]));
	return -1;
}

/* captura os atributos padr�o */
pthread_attr_init(&attr);

/* cria o thread */
pthread_create(&tid,&attr,runner,argv[1]);

/* agora espera o thread terminar */
pthread_join(tid,NULL);

/** exibe os n�meros primos */
for (i = 1; i <= atoi(argv[1]); i++)
	if (primes[i] > 0)
		printf("%d\n", i);
}

/**
 * Gera primos usando a Peneira de Erat�stenes.
 */
void *runner(void *param) 
{
int i, j;
int upper = atoi(param);

	primes[1] = 0;
	for (i = 2; i <= upper; i++)
		primes[i] = 1;

	for (i = 2; i <= upper/2; i++)
		for (j = 2; j <= upper/i; j++)
			primes[i*j] = 0;

	pthread_exit(0);
}
