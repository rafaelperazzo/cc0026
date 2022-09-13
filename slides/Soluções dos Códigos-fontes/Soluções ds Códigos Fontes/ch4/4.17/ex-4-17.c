/**
 * Programa usado no exercício 4.17
 *
 * Compilação:
 * 	gcc -lpthread ex-4-17.c
 */

#include <pthread.h>
#include <stdio.h> 
#include <sys/types.h>

int value = 0;
void *runner(void *param); /* o thread */

int main(int argc, char *argv[])
{
pid_t pid;
pthread_t tid; pthread_attr_t attr;

pid = fork();
	if (pid == 0) { /* processo filho */ 
		pthread_attr_init(&attr);
		pthread_create(&tid,&attr,runner,NULL); 
		pthread_join(tid,NULL);
		printf("CHILD: value = %d",value); /* LINE C */
	}
	else if (pid > 0) { /* processo pai */
		wait(NULL);
       	printf("PARENT: value = %d",value); /* LINE P */
	}
}

void *runner(void *param) { 
	value = 5;
	pthread_exit(0);
}
