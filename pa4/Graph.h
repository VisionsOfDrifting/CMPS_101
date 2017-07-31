/****************************************************************************************
*  Nicholas Pappas
*  nhpappas@ucsc.edu
*  CMPS 101 w/ Tantalo
*  Assignment: pa4
*****************************************************************************************/
//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include "List.h"

#define INF -2
#define NIL -1
// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;


// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object. 
Graph newGraph(int n);

// freeGraph()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph* pG);


// Access functions -----------------------------------------------------------

// getOrder()
// Returns the order (numVertices)
int getOrder(Graph G);

// getSize()
// Returns the size (numEdges)
int getSize(Graph G);

// getSource()
// Returns source vertex used last in BFS
int getSource(Graph G);

// getParent()
// Returns u's parent vertex in BFS Tree
// NIL if BFS() not yet called
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDist()
// Returns distance from source to u
// INF if BFS() not yet called
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u);

// getPath()
// Returns list of vertices in the shortest path
// Pre: getSource(G)!=NIL
// Pre: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u);


// Manipulation procedures ----------------------------------------------------

// makeNull()
// Resets Graph to its original (no edge) state
void makeNull(Graph G);

// addEdge()
// Inserts a new edge into the graph
// Pre: 1 <= u, v <= getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// Inserts a new directed edge into the graph
// Pre: 1 <= u, v <= getOrder(G)
void addArc(Graph G, int u, int v);

// BFS()
// Inserts a new edge into the graph
void BFS(Graph G, int s);

// Other Functions ------------------------------------------------------------

// printGraph()
// Prints data elements in G on a single line to stdout.
void printGraph(FILE* out, Graph G);

#endif
