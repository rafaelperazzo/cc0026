/**
 * zombie.c
 *
 * Esse pequeno programa gera um processo zumbi.
 *
* Um processo zumbi � criado quando um processo termina,
  * mas o pai n�o chama wait() e
  * continua a ser executado. Quando wait()n�o � chamado, o processo filho
  * mant�m uma entrada na tabela de entradas do processo
* e tamb�m mant�m seu pid.
 *
 * � muito f�cil:
 * 
 * (1) Crie um processo filho
 * (2) Fa�a o pai ser executado por um per�odo de tempo especificado.
 *
  * Se esse programa for executado em segundo plano, o estado do processo filho
 * o mostrar� como um processo zumbi.
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
		 * Apenas fa�a o filho terminar
		  * e transforme-o em um zumbi.
		 */

		return 0;
	}
	else {
		/**
		 * Fa�a o pai entrar em suspens�o por 10 segundos
		 */

		sleep(100);

		printf("Parent exiting\n");

		return 0;
	}
}
