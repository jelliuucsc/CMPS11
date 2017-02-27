//-----------------------------------------------------------------------------
// GraphClient.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[])
{
    int i, n=11;
    List S = newList();
    Graph G = newGraph(n);
    Graph T=NULL, C=NULL;

    for(i=1; i<=n; i++) append(S, i);

    addArc(G, 1,2);
    addArc(G, 2,5);
    addArc(G, 3,2);
    addArc(G, 3,5);
    addArc(G, 4,1);
    addArc(G, 5,4);
    addArc(G, 6,3);
    addArc(G, 6,5);
    addArc(G, 6,9);
    addArc(G, 6,10);
    addArc(G, 7,3);
    addArc(G, 7,6);
    addArc(G, 8,4);
    addArc(G, 9,4);
    addArc(G, 9,5);
    addArc(G, 9,8);
    addArc(G, 10,9);
    addArc(G, 10,11);
    addArc(G, 11,7);
    printGraph(stdout, G);

    DFS(G, S);
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for(i=1; i<=n; i++)
    {
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
    }
    fprintf(stdout, "\n");
    printList(stdout, S);
    fprintf(stdout, "\n");

    T = transpose(G);
    C = copyGraph(G);
    fprintf(stdout, "\n");
    printGraph(stdout, C);
    fprintf(stdout, "\n");
    printGraph(stdout, T);
    fprintf(stdout, "\n");

    DFS(T, S);
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for(i=1; i<=n; i++)
    {
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
    }
    fprintf(stdout, "\n");
    printList(stdout, S);
    fprintf(stdout, "\n");

    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);
    return(0);
}

