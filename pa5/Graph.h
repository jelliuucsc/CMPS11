//-----------------------------------------------------------------------------
// Jerry Liu
// jelliu
// CMPS101
// pa4
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------
/*** Constructors-Destructors ***/
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define WHITE 101
#define GRAY  201
#define BLACK 301
#define UNDEF -101
#define NIL -1
#define INF  1

#include "List.h"
typedef struct GraphObj* Graph;
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);

#endif
