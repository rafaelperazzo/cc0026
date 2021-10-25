#include <stdio.h>
#include <unistd.h>

int main(void) {
   pid_t pid = fork();
   if (pid<0) {
       printf("Falha ao criar o processo!\n");
   }
   else if (pid==1) { //Processo filho
        printf("[FILHO]: PID %d - PPID: %d\n",getpid(),getppid());
   }
   else { //Processo pai
        printf("[PAI]: PID %d - PPID: %d\n",getpid(),getppid());
   }
   return 0;
}
