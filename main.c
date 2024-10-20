#include <stdio.h>
#include <stdlib.h>
#include "disassembler.h"
#include "disassembler.c"

int main(int argc, char**argv) {
    /* 
    Main objectives here: 
    - Open file of 8080 code.
    - Read into buffer.
    - Skip through buffer calling our Disassemble8080 function above.
    - Advance by the return value of Disassemble8080.
    - Close once at the end of the buffer.
    */

   FILE *f = fopen(argv[1], "rb");
   if (f==NULL)
   {
    printf("Error could open file: %s\n.", argv[1]);
    exit(EXIT_FAILURE);
   }

   // Get file size and read it into a memory buffer
   fseek(f, 0L, SEEK_END);
   int fsize = ftell(f);
   fseek(f, 0L, SEEK_SET);
   printf("size of an int in this implementation: %d \n", (int)sizeof(int));
   printf("file size int: %d \n", fsize);

   unsigned char *buffer = malloc(fsize);

   fread(buffer, fsize, 1, f);
   fclose(f);

   int pc = 0;
   while (pc < fsize)
   {
    pc += Disassemble8080(buffer, pc);
   }
    
}