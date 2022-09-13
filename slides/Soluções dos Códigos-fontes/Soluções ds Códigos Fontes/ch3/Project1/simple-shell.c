/**
 * Solu��o para o programa de interface de shell.
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
#define MAX_COMMANDS	5 /* tamanho do hist�rico */

char history[MAX_COMMANDS][MAX_LINE];
char display_history [MAX_COMMANDS][MAX_LINE];

int command_count = 0;

/**
 * Adiciona o comando mais recente ao hist�rico.
 */

void addtohistory(char inputBuffer[]) {
	int i = 0;
	
	// adiciona o comando ao hist�rico
	strcpy(history[command_count % MAX_COMMANDS], inputBuffer);
	
	// adiciona o comando de estilo de exibi��o ao hist�rico
	while (inputBuffer[i] != '\n' && inputBuffer[i] != '\0') {
		display_history[command_count % MAX_COMMANDS][i] = inputBuffer[i];
		i++;
	}
	display_history[command_count % MAX_COMMANDS][i] = '\0';
	
	++command_count;

	return;
}

/** 
 * A fun��o de configura��o abaixo n�o retornar� nenhum valor, apenas far� a leitura
 * na pr�xima linha de comando; separe-a em argumentos distintos (usando espa�os em branco como
 * delimitadores) e configure as entradas do array args para apontar para o come�o do que se tornar�o
 * strings de estilo C terminadas em null. 
 */

int setup(char inputBuffer[], char *args[],int *background)
{
    int length,		/* n�mero de caracteres na linha de comando */
	i,				/* �ndice de loop para o acesso ao array inputBuffer */
	start,			/* �ndice do come�o do pr�ximo par�metro do comando */
	ct,				/* �ndice de onde inserir o pr�ximo par�metro em args[] */
	command_number;	/* �ndice do n�mero do comando solicitado */
    
    ct = 0;
	
    /* l� o que o usu�rio inseriu na linha de comando */
	do {
		printf("osh>");
		fflush(stdout);
		length = read(STDIN_FILENO,inputBuffer,MAX_LINE); 
	}
	while (inputBuffer[0] == '\n'); /* ignora caracteres de nova linha */
	
    /**
	 *  0 � o descritor de arquivo predefinido do sistema para stdin (entrada padr�o),
     *  que nesse caso � a tela do usu�rio. inputBuffer aparecendo sozinho � o
     *  mesmo que &inputBuffer[0], isto �, o endere�o inicial de onde armazenar 
     *  o comando que � lido, e length cont�m o n�mero de caracteres
     *  lidos. inputBuffer n�o � uma string C terminada em null. 
	 */
	
    start = -1;
    if (length == 0)
        exit(0);            /* ^d foi inserido, fim do fluxo de comando do usu�rio */
	
	/** 
	 * o sinal <control><d> interrompeu a chama de sistema read 
	 * se o processo estiver na chamada de sistema read(), read returnar� -1
  	 * No entanto, se isso ocorrer, errno ser� configurado com EINTR. Podemos verificar esse valor 
  	 * e desconsiderar o valor -1 
	 */
    if ( (length < 0) && (errno != EINTR) ) {
		perror("error reading the command");
		exit(-1);           /* termina com o c�digo de erro -1 */
    }
	
	/**
	 * Verifica se est�o usando hist�rico
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
		else if (isdigit(inputBuffer[1])) { /* recupera o en�simo comando */
			command_number = atoi(&inputBuffer[1]);
			strcpy(inputBuffer,history[command_number]);
			length = strlen(inputBuffer) + 1;
		}
	}
	
	
	/**
	 * Adiciona o comando ao hist�rico
	 */
	
	addtohistory(inputBuffer);
	
	/**
	 * Analisa o conte�do de inputBuffer
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
				
			case '\n':                 /* deve ser o �ltimo caractere examinado */
				if (start != -1){
					args[ct] = &inputBuffer[start];     
		    		ct++;
				}
				inputBuffer[i] = '\0';
				args[ct] = NULL; /* n�o h� mais argumentos nesse comando */
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
	 * Se encontrarmos &, n�o insira-o no array args
	 */
	
	if (*background)
		args[--ct] = NULL;
	
	args[ct] = NULL; /* apenas para o caso da linha da entrada ter um tamanho > 80 */
	
	return 1;
	
} /* fim da rotina de configura��o */


int main(void)
{
	char inputBuffer[MAX_LINE]; 	/* buffer para conter o comando inserido */
	int background;             	/* igual a 1 se um comando for seguido por '&' */
	char *args[MAX_LINE/2 + 1];	/* linha de comando (de tamanho 80) tem no m�ximo 40 argumentos */
	pid_t child;            		/* id do processo filho */
	int status;           		/* resultado da chamada de sistema */
	int shouldrun = 1;
	
	int i, upper;
		
    while (shouldrun){            		/* O programa termina normalmente dentro da configura��o */
		background = 0;
		
		shouldrun = setup(inputBuffer,args,&background);       /* acessa o pr�ximo comando */
		
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
					break; /* perror � uma rotina da biblioteca que exibe uma mensagem de erro do sistema, de acordo com o valor da vari�vel "errno" que ser� configurada durante uma fun��o como fork) que n�o conseguiu concluir sua tarefa 
                        com sucesso.*/
				
				case 0: /* esse � o processo filho */
					status = execvp(args[0],args);
					if (status != 0){
						perror("error in execvp");
						exit(-2); /* termina esse processo com c�digo de erro -2*/
					}
					break;
				
				default :  /* esse � o pai */
					if (background == 0) /* manipula o pai, espera o filho*/
						while (child != wait(NULL)) 
							;
			}
		}
    }
	
	return 0;
}
