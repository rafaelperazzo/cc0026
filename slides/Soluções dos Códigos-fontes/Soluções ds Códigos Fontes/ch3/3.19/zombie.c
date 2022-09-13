/**
 * zombie.c
 *
 * Esse pequeno programa gera um processo zumbi.
 *
* Um processo zumbi é criado quando um processo termina,
  * mas o pai não chama wait() e
  * continua a ser executado. Quando wait()não é chamado, o processo filho
  * mantém uma entrada na tabela de entradas do processo
* e também mantém seu pid.
 *
 * É muito fácil:
 * 
 * (1) Crie um processo filho
 * (2) Faça o pai ser executado por um período de tempo especificado.
 *
  * Se esse programa for executado em segundo plano, o estado do processo filho
 * o mostrará como um processo zumbi.
 * (Z abaixo do campo S usando ps)  
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(void)
{
	pid_t pid;

	pid = fork();

	if (pid < 0) {
		fprintf(stderr,"Unable to create child process\n");

		return -1;
	}
	else if (pid == 0) {
		/**
		 * Apenas faça o filho terminar
		  * e transforme-o em um zumbi.
		 */

		return 0;
	}
	else {
		/**
		 * Faça o pai entrar em suspensão por 10 segundos
		 */

		sleep(100);

		printf("Parent exiting\n");

		return 0;
	}
}
