/**
 * Esse é o processo produtor que grava a sequência de Collatz  
 * na região de memória compartilhada.
 *
 * Fundamentos de Sistemas Operacionais, Nona Edição
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

	/* cria o segmento de memória compartilhada */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* configura o tamanho do segmento de memória compartilhada */
	ftruncate(shm_fd,SIZE);

	agora mapeia o segmento de memória compartilhada no espaço de endereço do processo */
	ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

	/**
	 * Grava a sequência de Collatz na região de memória compartilhada.
 	 *
	 * Lembre-se de que devemos incrementar o valor de ptr após cada gravação.
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
