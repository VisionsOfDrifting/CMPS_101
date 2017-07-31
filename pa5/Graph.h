/****************************************************************************************
*  Nicholas Pappas
*  nhpappas@ucsc.edu
*  CMPS 101 w/ Tantalo
*  Assignment: pa5
*****************************************************************************************/
//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include "List.h"

#define UNDEF -2
#define NIL 0
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

// getParent()
// Returns u's parent vertex in DFS Tree
// NIL if DFS() not yet called
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDiscover()
// Returns discover time of a vertex u
// UNDEF if DFS() not yet called
// Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u);

// getFinish()
// Returns finish time of a vertex u
// UNDEF if DFS() not yet called
// Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u);


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

// DFS()
// Inserts a new edge into the graph
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S);

// Other Functions ------------------------------------------------------------

// transpose()
// returns the transpose of this graph
Graph transpose (Graph G);

// copyGraph()
// returns a new Graph with the same entries as this Graph
Graph copyGraph(Graph G);

// printGraph()
// Prints data elements in G on a single line to stdout.
void printGraph(FILE* out, Graph G);

#endif
