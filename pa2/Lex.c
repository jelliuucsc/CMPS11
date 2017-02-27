//-----------------------------------------------------------------------------
//  Jerry Liu
//  jelliu
//  CMPS101
//  pa2
//  Lex.c
//  A test client for the List ADT. Use this to test your list module.
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 160
int main(int argc, char* argv[])
{
    char line[MAX_LEN];
    FILE *in, *out;

    int lineNumber = 0;

    if( argc != 3 )
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

// open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if( in==NULL )
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if( out==NULL )
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    while(fgets(line, MAX_LEN, in) != NULL)
    {
        lineNumber++;
    }

    fclose(in);

    char* strArray[lineNumber];
    int i;
    for(i = 0; i < lineNumber; i++)
    {
        strArray[i] = calloc(1, sizeof(char* [MAX_LEN]) );
    }

    in = fopen(argv[1], "r");

    lineNumber = 0;
    while( fgets(line, MAX_LEN, in) != NULL )
    {
        strcpy(strArray[lineNumber], line);
        lineNumber++;
    }
    fclose(in);

    List L = newList();

    for (i = 0; i < lineNumber; i++)
    {
        int isInsert = 0;
        for (moveFront(L); index(L)>= 0; moveNext(L) )
        {
            if (strcmp(strArray[i], strArray[get(L)]) < 0)
            {
                insertBefore(L,i);
                isInsert = 1;
                break;
            }
        }
        if (isInsert == 0)
        {
            append(L,i);
        }
    }

    for (moveFront(L); index(L)>= 0; moveNext(L) )
    {
       fprintf(out, "%s", strArray[get(L)]);
    }
    //printList(out, L);

    return(0);
}
