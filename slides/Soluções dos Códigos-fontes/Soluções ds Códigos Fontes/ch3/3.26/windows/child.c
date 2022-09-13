/**
 * child.c
 *
 * Esse programa lê uma mensagem no pipe, muda a caixa de cada letra
 * e grava o resultado novamente no pipe.
 * Por exemplo, se a mensagem 'Hello' fosse lida, ele a mudaria para
 * 'hELLO' e gravaria essa mensagem no pipe.
 */
   
#include <stdio.h>
#include <windows.h>
#include <ctype.h>

#define BUFFER_SIZE 25

int main(VOID)
{
    HANDLE ReadHandle, WriteHandle; 
    CHAR buffer[BUFFER_SIZE];
    DWORD read, written, i;
    BOOL success;
    
    ReadHandle = GetStdHandle(STD_INPUT_HANDLE);
    WriteHandle= GetStdHandle(STD_OUTPUT_HANDLE);
    
    // agora faz o filho ler no pipe
    success = ReadFile(ReadHandle, buffer, BUFFER_SIZE, &read, NULL);
    
    // temos de exibir em stderr quando stdout é redirecionada para o pipe
    if (success)
       fprintf(stderr,"child: message = >%s<\n", buffer);
    else {
        fprintf(stderr, "child: error reading from pipe\n");
    
        return -1;
    }
    
    // agora grava algo no pipe
    for (i = 0; i < strlen(buffer); i++)
        if (isupper(buffer[i]))
           buffer[i] = tolower(buffer[i]);
        else
            buffer[i] = toupper(buffer[i]);
            
    if (!WriteFile(WriteHandle, buffer, BUFFER_SIZE, &written, NULL))
       fprintf(stderr, "Error writing to pipe\n");
    
    return 0;
}
