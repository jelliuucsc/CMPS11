//-----------------------------------------------------------------------------
// Jerry Liu
// jelliu
// CMPS101
// pa4
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

typedef struct GraphObj
{
    List *adjList;
    int *color;
    int *parent;
    int *discover;
    int *finish;
    int order;
    int size;
    int source;
    int time;

} GraphObj;
/*** Constructors-Destructors ***/
Graph newGraph(int n)
{
    Graph g = malloc(sizeof(GraphObj));
    g->adjList = calloc((n+1), sizeof(List));
    g->color = calloc((n+1), sizeof(int));
    g->parent = calloc((n+1), sizeof(int));
    g->discover = calloc((n+1), sizeof(int));
    g->finish = calloc((n+1), sizeof(int));
    g->order = n;
    g->source = NIL;
    g->size = 0;
    g->time = 0;

    int i;
    for(i = 0 ; i <= n; i++)
    {
        g->adjList[i] = newList();
        g->color[i] = WHITE;
        g->parent[i] = NIL;
        g->discover[i] = UNDEF;
        g->finish[i] = UNDEF;
    }

    return g;
}
void freeGraph(Graph* pG)
{
    if (pG != NULL && *pG != NULL)
    {
        int i;
        for (i = 0; i < ((*pG)->order); i++)
        {
            freeList(&(*pG)->adjList[i]);
        }

        free((*pG)->color);
        free((*pG)->discover);
        free((*pG)->finish);
        free((*pG)->parent);
        free((*pG)->adjList);

        free(*pG);
        *pG = NULL;

        return;
    }
}
/*** Access functions ***/
int getOrder(Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Error cannot getOrder() for empty Graph");
        exit(1);
    }

    return (G->order);
}
int getSize(Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Error cannot getSize() for empty Graph");
        exit(1);
    }
    return (G->size);
}
int getSource(Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Error cannot getSource() for empty Graph");
        exit(1);
    }
    return (G->source);
}

int getParent(Graph G, int u)
{
    if( u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Error cannot getParent for given vertex");
        exit(1);
    }
    return G->parent[u];
}
int getDiscover(Graph G, int u)
{
    if( u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Error cannot getSource() for empty Graph");
    }
    return G->discover[u];
}
int getFinish(Graph G, int u)
{
    if( u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Error cannot getDist for given vertex");
        exit(1);
    }
    return G->finish[u];

}
/*void getPath(List L, Graph G, int u)
{
    if(getSource(G) == NIL)
    {
        fprintf(stderr,"Error cannot getPath() for vertex with no edge");
        exit(1);
    }
    if(G == NULL)
    {
        fprintf(stderr, "Error cannot getPath() for an empty Graph");
        exit(1);
    }
    if( u < 1 || u > getOrder(G))
    {
        fprintf(stderr,"Error cannot getPath() for out of bound vertex");
        exit(1);
    }
    int s = G->source;
    if( u == s)
    {
        prepend(L , s);
        return;
    }
    else if( G->parent[u] == NIL)
    {
        prepend(L, NIL);
    }
    else
    {
        prepend(L, u);
        getPath(L, G, G->parent[u]);
    }
}
*/
/*** Manipulation procedures ***/
/*void makeNull(Graph G)
{
    int i;
    for(i = 1; i <= getOrder(G); i++)
    {
        clear(G->adjList[i]);
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
}
*/
void addEdge(Graph G, int u, int v)
{
    if(u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Error cannot addEdge() for out of bound vertex");
        exit(1);
    }
    if(v < 1 || v > getOrder(G))
    {
        fprintf(stderr, "Error cannot addEdge() for out of bound vertex");
        exit(1);
    }
    addArc(G, u, v);
    addArc(G, v, u);
}
void addArc(Graph G, int u, int v)
{
    if(u < 1 || u > getOrder(G))
    {
        fprintf(stderr, "Error cannot addArc() for out of bound vertex");
        exit(1);
    }
    if(v < 1 || v > getOrder(G))
    {
        fprintf(stderr, "Error cannot addArc() for out of bound vertex");
        exit(1);
    }
    List listU = G->adjList[u];
    if(length(listU) == 0)
    {
        prepend(listU, v);
        G->size++;
        return;
    }
    else
    {
        moveFront(listU);
        while(index(listU) != -1)
        {
            if(v == get(listU))
            {
                return;
            }
            else if(v > get(listU))
            {
                moveNext(listU);
            }
            else
            {
                insertBefore(listU, v);
                G->size++;
                return;
            }
        }
        append(listU, v);
        G->size++;
        return;
    }
}
void visit(Graph G, List S, int x)
{
    //printf("visit starts here:%d\n", x);
    if(G == NULL){
        fprintf(stderr, "Error G is NULL");
    }
    G->color[x] = GRAY;
    G->discover[x] = ++(G->time);
    List adjList = G->adjList[x];
    int y;
    for(moveFront(adjList); index(adjList) > -1; moveNext(adjList))
    {
        y = get(adjList);
        if(G->color[y] == WHITE)
        {
            G->parent[y] = x;
            visit(G, S, y);
        }
    }
    G->color[x] = BLACK;
    G->finish[x] = ++(G->time);
    prepend(S, x);
}
void DFS(Graph G, List S)
{
    int i;
    int j;
    if(G == NULL)
    {
        fprintf(stderr, "Graph is NULL");
        exit(1);
    }
    else if(length(S) == getSource(G))
    {
        fprintf(stderr, "The stack is full");
        exit(1);
    }
    for(i = 1; i <= getOrder(G); i++)
    {
        G->color[i] = WHITE;
        G->parent[i] = 0;
    }
    G->time = 0;
    for(moveFront(S); index(S) > -1; moveNext(S))
    {
        if(G->color[get(S)] == WHITE)
        {

            visit(G, S, get(S));
        }
    }
    printf("size of G %d/n", getOrder(G));
    //printf("LIST IS: \n");
    //printList(stdout, S);
    for(j = 1; j <= getOrder(G); j++)
        {
            deleteBack(S);
        }
}


/*void BFS(Graph G, int s)
{
    int i;
    for(i = 1; i <= getOrder(G); i++)
    {
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->source = s;
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();
    append(Q,s);
    while(length(Q) > 0)
    {
        int x = front(Q);
        deleteFront(Q);
        List vert = G->adjList[x];
        for(moveFront(vert); index(vert) >= 0; moveNext(vert))
        {
            int y = get(vert);
            if(G->color[y] == WHITE)
            {
                G->color[y] = GRAY;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(Q,y);
            }
            G->color[x] = BLACK;
        }
    }
    freeList(&Q);
}
*/
/*** Other operations ***/
Graph transpose(Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Error G is NULL");
        exit(1);
    }
    Graph trans = newGraph(getOrder(G));
    int tmp;
    int i;
    List tempList;
    for(i = 1; i <= getOrder(G); i++)
    {
        tempList = G->adjList[i];
        for(moveFront(tempList); index(tempList) > -1 ; moveNext(tempList))
        {
            tmp = get(tempList);
            append(trans->adjList[tmp], i);
        }
    }
    return trans;
}
Graph copyGraph(Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Error G is NULL");
        exit(1);
    }
    Graph copy = newGraph(getOrder(G));
    int tmp;
    int i;
    List tempList;
    for(i = 1; i <=getOrder(G); i++)
    {
        tempList = G->adjList[i];
        for(moveFront(tempList); index(tempList) > -1 ; moveNext(tempList))
        {

            tmp = get(tempList);
            append(copy->adjList[i], tmp);
        }
    }
    return copy;
}
void printGraph(FILE* out, Graph G)
{
    int i;
    for(i = 1; i <= getOrder(G); i++)
    {
        fprintf(out, "%d: ", i);
        printList(out, G->adjList[i]);
        fprintf(out, "\n");
    }

}


