/**
 * Solução do Pthreads para o exercício 4.26
 *
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013.
 */

#include <pthread.h>
#include <stdio.h>

/** só permitiremos até 256 números de fibonacci */
#define MAX_SIZE 256

int fibs[MAX_SIZE];

void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
int i;
pthread_t tid; /* identificador do  thread */
pthread_attr_t attr; /* configuração de atributos do thread */

if (argc != 2) {
	fprintf(stderr,"usage: a.out <integer value>\n");
	return -1;
}

if (atoi(argv[1]) < 0) {
	fprintf(stderr,"Argument %d must be >= 0 \n",atoi(argv[1]));
	return -1;
}

/* captura os atributos padrão */
pthread_attr_init(&attr);

/* cria o thread */
pthread_create(&tid,&attr,runner,argv[1]);

/* agora espera o thread terminar */
pthread_join(tid,NULL);

/** exibe os números de Fibonacci */
for (i = 0; i < atoi(argv[1]); i++)
	printf("%d\n", fibs[i]);
}

/**
 * Gera primos usando a Peneira de Eratóstenes.
 */
void *runner(void *param) 
{
int i;
int upper = atoi(param);

	if (upper== 0)
		pthread_exit(0);
	else if (upper == 1)
		fibs[0] = 0;
	else if (upper== 2) {
		fibs[0] = 0;
		fibs[1] = 1;
	}
	else { // sequence > 2
		fibs[0] = 0;
		fibs[1] = 1;

		for (i = 2; i < upper; i++)
			fibs[i] = fibs[i-1] + fibs[i-2];
	}
		
	pthread_exit(0);
}
