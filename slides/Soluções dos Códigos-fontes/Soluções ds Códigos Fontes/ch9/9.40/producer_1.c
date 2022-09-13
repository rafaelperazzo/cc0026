/**
 * Illustrate memory-mapping files in Win32
 *
 * Producer code - generates the catalan sequence.s
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Eighth Edition
 * Copyright John Wiley & Sons - 2009.
 */

#include <windows.h>
#include <stdio.h>
#define SIZE 256

int factorial(int n) {
     if (n == 0)
        return 1;
     else
         return n * factorial(n-1);
}


// returns the nth catalan numbers
int catalan(int n) {
    
    return (factorial(2 * n) / (factorial(n + 1) * factorial(n)));
}

int main(int argc, char *argv[])
{
HANDLE hFile, hMapFile;
LPVOID mapAddress;
char series[SIZE];
char buf[SIZE];

int i, seriesSize = 0;

    seriesSize = atoi(argv[1]);
    

	// first create/open the file
	hFile = CreateFile("temp.txt",
						GENERIC_READ | GENERIC_WRITE,
						0,
						NULL,
						OPEN_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,
						NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
   		fprintf(stderr,"Could not open file temp.txt (%d).\n",GetLastError());
   		return -1;
	}

	// now obtain a mapping for it

	hMapFile = CreateFileMapping(hFile,
									NULL,
									PAGE_READWRITE,
									0,
									0,
									TEXT("SharedObject"));

	if (hMapFile == NULL) {
		fprintf(stderr,"Could not create mapping (%d).\n", GetLastError());
   		return -1;
	}

	// now establish a mapped viewing of the file

	mapAddress = MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,0);

	if(mapAddress == NULL) {
		printf("Could not map view of file (%d).\n", GetLastError());
		return -1;
	}

	// write to shared memory
	
	for (i = 1; i <= seriesSize; i++) {
        sprintf(buf, "%d, ", catalan(i));
        strcat(series,buf);
        //printf( "**%s**", buf);
        }
        
        sprintf((char *)mapAddress, "%s\n", series);
        
        

	//sprintf((char *)mapAddress,"%s","Shared memory message");

	while (1);
	// remove the file mapping
	UnmapViewOfFile(mapAddress);

	// close all handles
	CloseHandle(hMapFile);
	CloseHandle(hFile);
}

