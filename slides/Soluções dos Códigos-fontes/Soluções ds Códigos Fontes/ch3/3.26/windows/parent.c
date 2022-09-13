/*
 * parent.c
 *
 * Esse programa grava uma mensagem em um pipe e lê o resultado novamente no pipe.
 */
  
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BUFFER_SIZE 25

int main(VOID)
{
 HANDLE StdinRead, StdinWrite;      /* pipe para a gravação do pai para o filho */ 
 HANDLE StdoutRead, StdoutWrite;    /* pipe para a gravação do filho para o pai */
 STARTUPINFO si;
 PROCESS_INFORMATION pi;
 char message[BUFFER_SIZE] = "Greetings";
 DWORD read, written;
 BOOL success;
 
 /* configura atributos de segurança para que os handles do pipe sejam herdados */
 SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL,TRUE};

 /* aloca memória */
 ZeroMemory(&pi, sizeof(pi));
 
  /* cria o pipe de gravação do pai para o filho */
 if ( !CreatePipe(&StdinRead, &StdinWrite, &sa, 0)) {
    fprintf(stderr,"Create Pipe Failed\n");
    return 1;
 }
 
 /* cria o pipe de gravação do filho para o pai */
 if ( !CreatePipe(&StdoutRead, &StdoutWrite, &sa, 0)) {
    fprintf(stderr,"Create Pipe Failed\n");
    return 1;
 }
  
 /* estabelece a estrutura START_INFO do processo filho */
 GetStartupInfo(&si);
 si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
 
 /* redireciona a entrada padrão para a extremidade de leitura do pipe */
 si.hStdOutput = StdoutWrite;
 si.hStdInput = StdinRead;
 si.dwFlags = STARTF_USESTDHANDLES;
 
 /* cria o processo filho */
 if (!CreateProcess(NULL, 
                     ".//child.exe",
                     NULL,
                     NULL,
                     TRUE, /* herda handles */
                     0,
                     NULL,
                     NULL,
                     &si,
                     &pi))
  {
     fprintf(stderr, "Process Creation Failed\n");
     return -1;
  }
               
 /* fecha as extremidades não usadas do pipe */
 CloseHandle(StdoutWrite);
 CloseHandle(StdinRead);
       
 /* agora o pai quer gravar no pipe */
 if (!WriteFile (StdinWrite, message, BUFFER_SIZE, &written, NULL))
    fprintf(stderr, "Error writing to pipe\n");
    
 /* fecha a extremidade de gravação do pipe */
 CloseHandle(StdinWrite);
 
 /* agora o pai quer graver no pipe */
 success = ReadFile(StdoutRead, message, BUFFER_SIZE, &read, NULL);
 if (success)
    printf("parent: message = >%s<\n",message);
 else {
      fprintf(stderr, "parent: Error reading from pipe\n");
      
      return -1;
 }
 
 /* fecha extremidade de leitura do pipe */
 CloseHandle(StdoutRead);
 
 /* espera o filho terminar */
 WaitForSingleObject(pi.hProcess, INFINITE);  
 
 /* fecha todos os handles */
 CloseHandle(pi.hProcess);
 CloseHandle(pi.hThread);                 
}
