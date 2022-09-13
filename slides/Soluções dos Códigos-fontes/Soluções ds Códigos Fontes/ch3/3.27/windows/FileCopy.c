/*
 * FileCopy.c
 * 
 * Esse programa abre um arquivo e grava seu conteúdo em um pipe 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BUFFER_SIZE 25
#define STRING_SIZE 25

int main(int argc, char *argv[])
{
 HANDLE ReadHandle, WriteHandle, InputFile;
 STARTUPINFO si;
 PROCESS_INFORMATION pi;
 char buffer[BUFFER_SIZE];
 char child_command[STRING_SIZE];
 DWORD read, written;
 
 if (argc != 3) {
    fprintf(stderr, "Usage: FileCopy <source> <copy>");
    
    return -1;
 }
 
 /* agora abre o arquivo */
  InputFile = CreateFile(argv[1], GENERIC_READ, 0, NULL, 
  OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL); 

  if (InputFile == INVALID_HANDLE_VALUE) {
      fprintf(stderr,"CreateFile failed");
      
      return -1;
  }
  
 /* Constrói a string que contém o comando do filho */
 sprintf(child_command,".//child.exe %s",argv[2]);

 /* configura atributos de segurança para que os handles do pipe sejam herdados */
 SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL,TRUE};

 /* aloca memória */
 ZeroMemory(&pi, sizeof(pi));
 
  /* cria o pipe */
 if ( !CreatePipe(&ReadHandle, &WriteHandle, &sa, 0)) {
    fprintf(stderr,"Create Pipe Failed\n");
    return 1;
 }
 
 /* não queremos que o handle de gravação do pipe seja herdado */
 SetHandleInformation( WriteHandle, HANDLE_FLAG_INHERIT, 0);
  
 /* estabelece a estrutura START_INFO do processo filho */
 GetStartupInfo(&si);
 si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
 si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 /* redireciona a entrada padrão para a extremidade de leitura do pipe */
 si.hStdInput = ReadHandle;
 si.dwFlags = STARTF_USESTDHANDLES;
 
 /* cria o processo filho */
 if (!CreateProcess(NULL, 
                     //".\\child.exe",
                     child_command,
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
               
 /* grava o arquivo no pipe */
 for (;;) 
   { 
      if (! ReadFile(InputFile, buffer, BUFFER_SIZE, &read, NULL) || 
         read == 0) break; 
      if (! WriteFile(WriteHandle, buffer, read, &written, NULL)) 
         break; 
   } 
 
 CloseHandle(InputFile);
 /* fecha o pipe */
 CloseHandle(WriteHandle);

 // espera o filho terminar 
 WaitForSingleObject(pi.hProcess, INFINITE);  
 
 // fecha todos os handles
 CloseHandle(pi.hProcess);
 CloseHandle(pi.hThread);                 
}
