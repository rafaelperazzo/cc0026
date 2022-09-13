/**
 * Solu��o do projeto 2
 *
 * Operating System Concepts - Ninth Edition
 * John Wiley & Sons - 2013.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE				10
#define NUMBER_OF_THREADS	3

void *sorter(void *params);	/* thread que executa o algoritmo de classifica��o b�sico */
void *merger(void *params);	/* thread que executa a mesclagem de resultados */

int list[SIZE] = {7,12,19,3,18,4,2,6,15,8};

int result[SIZE];

typedef struct
{
	int from_index;
	int to_index;
} parameters;

int main (int argc, const char * argv[]) 
{
	int i;
    
	pthread_t workers[NUMBER_OF_THREADS];
	
	/* estabelece o primeiro thread de classifica��o */
	parameters *data = (parameters *) malloc (sizeof(parameters));
	data->from_index = 0;
	data->to_index = (SIZE/2) - 1;
	pthread_create(&workers[0], 0, sorter, data);
	
	/* estabelece o segundo thread de classifica��o */
	data = (parameters *) malloc (sizeof(parameters));
	data->from_index = (SIZE/2);
	data->to_index = SIZE - 1;
	pthread_create(&workers[1], 0, sorter, data);
	
	/* agora espera os 2 threads de classifica��o terminarem */
	for (i = 0; i < NUMBER_OF_THREADS - 1; i++)
		pthread_join(workers[i], NULL);
	
	/* estabelece o thread de mesclagem */
	data = (parameters *) malloc(sizeof(parameters));
	data->from_index = 0;
	data->to_index = (SIZE/2);
	pthread_create(&workers[2], 0, merger, data);
	
	/* espera o thread de mesclagem terminar */
	pthread_join(workers[2], NULL);

	/* exibe o array classificado */
	for (i = 0; i < SIZE; i++)
		printf("%d  ",result[i]);
	printf("\n");
	
    return 0;
}

/**
 * Thread de classifica��o.
 *
 * Esse thread pode usar basicamente qualquer algoritmo na classifica��o
 */

void *sorter(void *params)
{
	int i;
	parameters* p = (parameters *)params;
	
	int begin = p->from_index;
	int end = p->to_index;
	
	int swapped = 1;
	int j = 0;
	int temp;
	
	while (swapped == 1) {
		swapped = 0;
		j++;
		
		for (i = begin; i <= end - j; i++) {
			if (list[i] > list[i+1]) {
				temp = list[i];
				list[i] = list[i+1];
				list[i+1] = temp;
				swapped = 1;
			}
		}
	}

	pthread_exit(0);
}

/**
 * Thread de mesclagem
 *
 * Usa a classifica��o por mesclagem para mesclar duas sublistas
 */

void *merger(void *params)
{
	parameters* p = (parameters *)params;
	
	int i,j;
	
	i = p->from_index;
	j = p->to_index;
	
	int position = 0;	/* a posi��o da inser��o na lista de resultados */
	
	while (i < p->to_index && j < SIZE) {
		if (list[i] <= list[j]) {
			result[position++] = list[i];
			i++;
		}
		else {
			result[position++] = list[j];
			j++;
		}
	}
		
	/* copia o resto */
	if (i < p->to_index) {
		while (i < p->to_index) {
			result[position] = list[i];
			position++;
			i++;
		}
	}
	else {
		while (j < SIZE) {
			result[position] = list[j];
			position++;
			j++;
		}
	}

		
	
	pthread_exit(0);
}

