#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
   pid_t pid = fork();
   if (pid<0) {
       printf("Falha ao criar o processo!\n");
   }
   else if (pid==0) { //Processo filho
        printf("Executando um programa externo...\n");
        printf("[FILHO]: PID %d - PPID: %d\n",getpid(),getppid());
        execlp("/usr/bin/ls","ls","-la",(char*) NULL);
        printf("Finalizando a execucao...\n");
   }
   else { //Processo pai
        printf("[PAI]: PID %d - PPID: %d\n",getpid(),getppid());
        wait(NULL);
   }
   return 0;
}