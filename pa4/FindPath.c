//-----------------------------------------------------------------------------
// Jerry Liu
// jelliu
// CMPS101
// pa4
// FindPath.c
// A test client for Graph ADT.
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[])
{
    char line[MAX_LEN];
    FILE *in, *out;

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

    fgets(line, MAX_LEN , in);
    int i = 0;
    sscanf(line, "%d", &i);

    Graph g = newGraph(i);
    int u=0, v=0;
    while(fgets(line, MAX_LEN, in) != NULL)
    {
        sscanf(line, "%d %d", &u, &v);

        if( u == 0 && v == 0)
        {
            break;
        }
        else
        {
            addEdge(g, u ,v);
        }
    }

    printGraph(out, g);

    u = 0;
    v = 0;
    List L = newList();
    while(fgets(line, MAX_LEN, in) != NULL)
    {
        sscanf(line, "%d %d", &u, &v);
        if( u == 0 && v == 0)
        {
            break;
        }
        else
        {
            BFS(g, u);
            printPath(g, u , v, L, out);
        }

    }
    freeList(&L);
    freeGraph(&g);
    fclose(out);
    fclose(in);
    return(0);
}

void printPath(Graph G, int u, int v, List L, FILE* out)
{
    getPath(L,G,v);
    if(v == -1)
    {
        fprintf(out,"\n");
        fprintf(out,"The Distance from %d to %d is infinity", getSource(G), v);
        fprintf(out,"No %d-%d path exists\n",getSource(G), v);
    }
    else
    {
        fprintf(out,"\n");
        fprintf(out,"The distance from %d to %d is %d\n",getSource(G), v, getDist(G,v));
        fprintf(out,"A shortest %d-%d path is: ",getSource(G), v);
        printList(out,L);
        fprintf(out, "\n");
        clear(L);
    }
}
