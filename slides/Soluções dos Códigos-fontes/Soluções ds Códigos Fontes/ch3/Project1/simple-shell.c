/**
 * Solução para o programa de interface de shell.
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>


#define MAX_LINE		80 /* 80 caracteres por linha, por comando, devem ser suficientes. */
#define MAX_COMMANDS	5 /* tamanho do histórico */

char history[MAX_COMMANDS][MAX_LINE];
char display_history [MAX_COMMANDS][MAX_LINE];

int command_count = 0;

/**
 * Adiciona o comando mais recente ao histórico.
 */

void addtohistory(char inputBuffer[]) {
	int i = 0;
	
	// adiciona o comando ao histórico
	strcpy(history[command_count % MAX_COMMANDS], inputBuffer);
	
	// adiciona o comando de estilo de exibição ao histórico
	while (inputBuffer[i] != '\n' && inputBuffer[i] != '\0') {
		display_history[command_count % MAX_COMMANDS][i] = inputBuffer[i];
		i++;
	}
	display_history[command_count % MAX_COMMANDS][i] = '\0';
	
	++command_count;

	return;
}

/** 
 * A função de configuração abaixo não retornará nenhum valor, apenas fará a leitura
 * na próxima linha de comando; separe-a em argumentos distintos (usando espaços em branco como
 * delimitadores) e configure as entradas do array args para apontar para o começo do que se tornarão
 * strings de estilo C terminadas em null. 
 */

int setup(char inputBuffer[], char *args[],int *background)
{
    int length,		/* número de caracteres na linha de comando */
	i,				/* índice de loop para o acesso ao array inputBuffer */
	start,			/* índice do começo do próximo parâmetro do comando */
	ct,				/* índice de onde inserir o próximo parâmetro em args[] */
	command_number;	/* índice do número do comando solicitado */
    
    ct = 0;
	
    /* lê o que o usuário inseriu na linha de comando */
	do {
		printf("osh>");
		fflush(stdout);
		length = read(STDIN_FILENO,inputBuffer,MAX_LINE); 
	}
	while (inputBuffer[0] == '\n'); /* ignora caracteres de nova linha */
	
    /**
	 *  0 é o descritor de arquivo predefinido do sistema para stdin (entrada padrão),
     *  que nesse caso é a tela do usuário. inputBuffer aparecendo sozinho é o
     *  mesmo que &inputBuffer[0], isto é, o endereço inicial de onde armazenar 
     *  o comando que é lido, e length contém o número de caracteres
     *  lidos. inputBuffer não é uma string C terminada em null. 
	 */
	
    start = -1;
    if (length == 0)
        exit(0);            /* ^d foi inserido, fim do fluxo de comando do usuário */
	
	/** 
	 * o sinal <control><d> interrompeu a chama de sistema read 
	 * se o processo estiver na chamada de sistema read(), read returnará -1
  	 * No entanto, se isso ocorrer, errno será configurado com EINTR. Podemos verificar esse valor 
  	 * e desconsiderar o valor -1 
	 */
    if ( (length < 0) && (errno != EINTR) ) {
		perror("error reading the command");
		exit(-1);           /* termina com o código de erro -1 */
    }
	
	/**
	 * Verifica se estão usando histórico
	 */
	
	if (inputBuffer[0] == '!') {
		if (command_count == 0) {
			printf("No history\n");
			return 1;
		}
		else if (inputBuffer[1] == '!') {
			// restaura o comando anterior
			strcpy(inputBuffer,history[(command_count - 1) % MAX_COMMANDS]);
			length = strlen(inputBuffer) + 1;
		}
		else if (isdigit(inputBuffer[1])) { /* recupera o enésimo comando */
			command_number = atoi(&inputBuffer[1]);
			strcpy(inputBuffer,history[command_number]);
			length = strlen(inputBuffer) + 1;
		}
	}
	
	
	/**
	 * Adiciona o comando ao histórico
	 */
	
	addtohistory(inputBuffer);
	
	/**
	 * Analisa o conteúdo de inputBuffer
	 */
	
    for (i=0;i<length;i++) { 
		/* examina cada caractere de inputBuffer */
		
        switch (inputBuffer[i]){
			case ' ':
			case '\t' :               /* separadores de argumentos */
				if(start != -1){
              		args[ct] = &inputBuffer[start];    /* configura o ponteiro */
		    		ct++;
				}
				inputBuffer[i] = '\0'; /* adiciona um caractere nulo; cria uma string C */
				start = -1;
				break;
				
			case '\n':                 /* deve ser o último caractere examinado */
				if (start != -1){
					args[ct] = &inputBuffer[start];     
		    		ct++;
				}
				inputBuffer[i] = '\0';
				args[ct] = NULL; /* não há mais argumentos nesse comando */
				break;
				
	    	default :             /* algum outro caractere */
				if (start == -1)
		    		start = i;
              	if (inputBuffer[i] == '&') {
	    			*background  = 1;
                   	inputBuffer[i-1] = '\0';
				}
		} /* fim de switch */
	}    /* fim de for */
	
	/**
	 * Se encontrarmos &, não insira-o no array args
	 */
	
	if (*background)
		args[--ct] = NULL;
	
	args[ct] = NULL; /* apenas para o caso da linha da entrada ter um tamanho > 80 */
	
	return 1;
	
} /* fim da rotina de configuração */


int main(void)
{
	char inputBuffer[MAX_LINE]; 	/* buffer para conter o comando inserido */
	int background;             	/* igual a 1 se um comando for seguido por '&' */
	char *args[MAX_LINE/2 + 1];	/* linha de comando (de tamanho 80) tem no máximo 40 argumentos */
	pid_t child;            		/* id do processo filho */
	int status;           		/* resultado da chamada de sistema */
	int shouldrun = 1;
	
	int i, upper;
		
    while (shouldrun){            		/* O programa termina normalmente dentro da configuração */
		background = 0;
		
		shouldrun = setup(inputBuffer,args,&background);       /* acessa o próximo comando */
		
		if (strncmp(inputBuffer, "exit", 4) == 0)
			return 0;
		else if (strncmp(inputBuffer,"history", 7) == 0) {
			if (command_count < MAX_COMMANDS)
				upper = command_count;
			else 
				upper = MAX_COMMANDS;
			
			for (i = 0; i < upper; i++) {
				printf("%d \t %s\n", i, display_history[i]);
			}
			
			continue;
		}

				
		if (shouldrun) {
			child = fork();          /* cria um processo duplicata! */
			switch (child) {
				case -1: 
					perror("could not fork the process");
					break; /* perror é uma rotina da biblioteca que exibe uma mensagem de erro do sistema, de acordo com o valor da variável "errno" que será configurada durante uma função como fork) que não conseguiu concluir sua tarefa 
                        com sucesso.*/
				
				case 0: /* esse é o processo filho */
					status = execvp(args[0],args);
					if (status != 0){
						perror("error in execvp");
						exit(-2); /* termina esse processo com código de erro -2*/
					}
					break;
				
				default :  /* esse é o pai */
					if (background == 0) /* manipula o pai, espera o filho*/
						while (child != wait(NULL)) 
							;
			}
		}
    }
	
	return 0;
}
