/**
 * Programa que mascara o n�mero e o deslocamento da p�gina em um
 * endere�o de 32 bits sem sinal.
 * O tamanho de uma p�gina � de 4 KB (12 bits)
 *
 * Uma referencia � mem�ria aparece como:
 *
 * |------------|-----|
 *  31	    12 11  0
 *
 */

#include <stdio.h>
#include <unistd.h>

#define PAGE_NUMBER_MASK 0xFFFFF000
#define OFFSET_MASK 0x00000FFF

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr,"Usage: ./a.out <virtual address>\n");
		return -1;
	}

	int page_num, offset;
	unsigned int reference;

	reference = (unsigned int)atoi(argv[1]);
	printf("The address %d contains:\n",reference);

	// primeiro mascara o n�mero da p�gina 
	page_num = (reference & PAGE_NUMBER_MASK) >> 12;
	offset = reference & OFFSET_MASK;
	printf("page number = %d\n",page_num);
	printf("offset = %d\n",offset);

	return 0;
}
