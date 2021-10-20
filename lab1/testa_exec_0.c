#include <stdio.h>
#include <unistd.h>

int main()
{
     printf ("Eu sou o processo PID=%d e estou executando o programa testa_exec_0\n", getpid()) ;
     printf ("Vou fazer um exec() agora!\n") ;
     execl("/bizzz/lsz","lsz","-l", "testa_exec_0.c",NULL) ;
     printf ("Estou de volta! Vou continuar a execução do programa testa_exec_0\n") ;
     return 1;
}
