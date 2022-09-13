/*
 * child.c
 *
 * Esse programa l� o conte�do do pipe e grava-o em um arquivo.
 */
  
#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 10

int main(int argc, char *argv[])
{
    HANDLE ReadHandle, WriteHandle, OutputFileHandle; 
    CHAR buffer[BUFFER_SIZE];
    DWORD read, written;
    BOOL success;
    
    /* essa � a extremidade de leitura do pipe */
    ReadHandle = GetStdHandle(STD_INPUT_HANDLE);
    
    /* essa � a sa�da padr�o */
    WriteHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    /* handle do arquivo de sa�da */
    OutputFileHandle = CreateFile(/*"copy.txt"*/argv[1], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL, NULL);
    
    //fprintf(stderr,"child: started reading\n");
    // agora faz o filho ler no pipe e grava seu conte�do em copy.txt
    for (;;) {
        //printf("reading");
        if ( !ReadFile(ReadHandle, buffer, BUFFER_SIZE, &read, NULL))
           break;
        if (read == 0)
           break;
         
         //printf("read = %d >%s<\n",read, buffer);
         
         if (! WriteFile(OutputFileHandle, buffer, read, &written, NULL)) 
            break;    
    }
    
    //fprintf(stderr,"child: out of for loop\n");
    
    CloseHandle(ReadHandle);    
    CloseHandle(OutputFileHandle);
    
    return 0;
}
