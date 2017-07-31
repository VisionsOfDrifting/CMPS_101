/****************************************************************************************
*  Nicholas Pappas
*  nhpappas@ucsc.edu
*  CMPS 101 w/ Tantalo
*  Assignment: pa4
*****************************************************************************************/
//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "Graph.h"

//need not #define them, but I will use the convention
//white= 4, grey = 5, black = 6

// structs --------------------------------------------------------------------

// Exported type --------------------------------------------------------------
typedef struct GraphObj{
   List* IsAdjList;
   int* IsParent;
   int* IsDepth;
   int* IsColor; //I tried to use strings and got errors. So we will stick to ints
   int sizeNumE;
   int orderNumV;
   int sourceVertex;
}GraphObj;

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object. 
Graph newGraph(int n){
   Graph G;
   G = malloc(sizeof(struct GraphObj));
   assert(G!=NULL);
   G->IsAdjList = calloc(n+1, sizeof(List));
   assert(G->IsAdjList!=NULL);
   G->IsParent = calloc(n+1, sizeof(int));
   assert(G->IsParent!=NULL);
   G->IsDepth = calloc(n+1, sizeof(int));
   assert(G->IsDepth!=NULL);
   G->IsColor = calloc(n+1, sizeof(int));
   assert(G->IsColor!=NULL);
   G->sizeNumE = 0;
   G->orderNumV = n;
   G->sourceVertex =  NIL;
   //we will use AdjList[0] as our queue
   for(int i=0; i<(n+1); i++){
      G->IsAdjList[i] = newList();
	  G->IsParent[i] = NIL;
	  G->IsDepth[i] = INF;
	  G->IsColor[i] = 4;
   }
   return G;
}

// freeGraph()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph* pG){
   if( pG!=NULL && *pG!=NULL ){
	  for(int i=0; i<((*pG)->orderNumV+1); i++){
	     free((*pG)->IsAdjList[i]);
	  }
      free((*pG)->IsAdjList);
	  free((*pG)->IsColor);
	  free((*pG)->IsParent);
	  free((*pG)->IsDepth);
	  free(*pG);
      *pG = NULL;
   }
}


// Access functions -----------------------------------------------------------

// getOrder()
// Returns the order (numVertices)
int getOrder(Graph G){
	return G->orderNumV;
}

// getSize()
// Returns the size (numEdges)
int getSize(Graph G){
	return G->sizeNumE;
}

// getSource()
// Returns source vertex used last in BFS
int getSource(Graph G){
	return G->sourceVertex;
}

// getParent()
// Returns u's parent vertex in BFS Tree
// NIL if BFS() not yet called
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getParent() w/ vertex 'u' out of bounds\n");
      exit(1);
   }
   return G->IsParent[u];
}

// getDist()
// Returns distance from source to u
// INF if BFS() not yet called
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
   if(getSource(G) == NIL){
      return INF;
   }
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getOrder() w/ vertex 'u' out of bounds\n");
      exit(1);
   }
   return G->IsDepth[u];
}

// getPath()
// Returns list of vertices in the shortest path
// Pre: getSource(G)!=NIL
// Pre: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u){
   if(getSource(G) == NIL){
      printf("Graph Error: calling getPath() with NULL source\n"); 
   }
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getPath() w/ vertex 'u' out of bounds\n");
      exit(1);
   }
   int v = G->sourceVertex;
   if(u == v){ //we are at the source vertex, we are done recurring.
      prepend(L, v);
   }else if(G->IsParent[u] == NIL){ //if no such path exists because more than one tree exists
      append(L, NIL);
   }else{ //u is not the source. Add it to the list and go to its parent.
      prepend(L, u);
	  getPath(L, G, G->IsParent[u]);
   }
}

// Manipulation procedures ----------------------------------------------------

// makeNull()
// Resets Graph to its original (no edge) state
void makeNull(Graph G){
   for(int i=0; i<(getOrder(G)+1); i++){
      clear(G->IsAdjList[i]);
   }
}

// addEdge()
// Inserts a new edge into the graph
// Pre: 1 <= u, v <= getOrder(G)
void addEdge(Graph G, int u, int v){
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling addEdge() w/ vertex 'u' out of bounds\n");
      exit(1);
      }
	  addArc(G, v, u); //what is an edge? but two directed edges
	  addArc(G, u, v);
	  G->sizeNumE--; //we must account for the two size++. As this is just one edge
}

// addArc()
// Inserts a new directed edge into the graph
// Pre: 1 <= u, v <= getOrder(G)
void addArc(Graph G, int u, int v){
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling addArc() w/ vertex 'u' out of bounds\n");
      exit(1);
   }
   List L = G->IsAdjList[u];
   if(isEmpty(L)){ //list is not empty
      append(L, v);   
   }else{ //list is empty. We must use append to avoid the moveFront() on empty list error
	  moveFront(L);
      while( v > get(L) && index(L)!= -1){ //while we are on the list and v is greater than current entry
         moveNext(L);
      }
      if(index(L) == -1){ //we've fallen off the list.
         append(L, v);
      }else{ //we didn't fall off the list. v belongs before the current element.
        insertBefore(L, v);
      }
   }
   G->sizeNumE++;
}

// BFS()
// Inserts a new edge into the graph
void BFS(Graph G, int s){
   for(int i=0; i<(G->orderNumV + 1); i++){
      G->IsParent[i] = NIL;
	  G->IsDepth[i] = INF;
	  G->IsColor[i] = 4;
   }
   G->sourceVertex = s;
   G->IsDepth[s] = 0;
   G->IsColor[s] = 5; 
   //we will use IsAdjList[0] as the queue
   prepend(G->IsAdjList[0], s); //enqueue
   while(length(G->IsAdjList[0]) > 0){ //process adjLists
      moveBack(G->IsAdjList[0]);
	  int current = get(G->IsAdjList[0]); //dequeue
	  deleteBack(G->IsAdjList[0]);
	  moveFront(G->IsAdjList[current]);
	  while(index(G->IsAdjList[current]) != -1){ //process adjList
	     int v = get(G->IsAdjList[current]);
		 if(G->IsColor[v] == 4){
		    G->IsColor[v] = 5; //The colors are more off a reference thing than a functionality
			G->IsParent[v] = current;
			G->IsDepth[v] = G->IsDepth[current] + 1;
			prepend(G->IsAdjList[0], v); //enqueue
			G->IsColor[v] = 6;
		 }
		 moveNext(G->IsAdjList[current]);
	  }
	  //note that the queue should have cleared itself by finishing
   }
}

// Other Functions ------------------------------------------------------------

// printGraph()
// Prints data elements in G on a single line to stdout.
void printGraph(FILE* out, Graph G){
   if(out == NULL || G == NULL){
      printf("Graph Error: called printGraph() on a null reference");
      exit(1);
   }
   for(int i = 1; i<(getOrder(G)+1); i++) {
      fprintf(out, "%d: ", i);
      printList(out, G->IsAdjList[i]);
      fprintf(out, "\n");
   }
}
