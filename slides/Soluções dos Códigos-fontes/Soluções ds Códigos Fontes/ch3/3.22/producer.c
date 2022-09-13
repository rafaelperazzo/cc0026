/**
 * Esse � o processo produtor que grava a sequ�ncia de Collatz  
 * na regi�o de mem�ria compartilhada.
 *
 * Fundamentos de Sistemas Operacionais, Nona Edi��o
 * Copyright John Wiley & Sons, 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
	const int SIZE = 4096;
	const char *name = "COLLATZ";

	int shm_fd;
	void *ptr;
	char str[128];
	int n = atoi(argv[1]);

	/* cria o segmento de mem�ria compartilhada */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* configura o tamanho do segmento de mem�ria compartilhada */
	ftruncate(shm_fd,SIZE);

	agora mapeia o segmento de mem�ria compartilhada no espa�o de endere�o do processo */
	ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

	/**
	 * Grava a sequ�ncia de Collatz na regi�o de mem�ria compartilhada.
 	 *
	 * Lembre-se de que devemos incrementar o valor de ptr ap�s cada grava��o.
	 */

	sprintf(str,"%d, ", n);
	sprintf(ptr,"%s",str);
	while (n != 1) {
		ptr += strlen(str);

		if (n % 2 == 0)
			n = n / 2;
		else
			n = 3 * n + 1;

		sprintf(str,"%d, ", n);
		sprintf(ptr,"%s",str);
	}

	return 0;
}
