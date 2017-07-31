/****************************************************************************************
*  Nicholas Pappas
*  nhpappas@ucsc.edu
*  CMPS 101 w/ Tantalo
*  Assignment: pa6
*****************************************************************************************/
//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "Graph.h"

#define INF -2
#define NIL -1

//We need not #define colors.
//I will use the convention: white= 4, grey = 5, black = 6

// structs --------------------------------------------------------------------

// Exported type --------------------------------------------------------------
typedef struct GraphObj{
   List* IsAdjList;
   int* IsParent;
   int* IsDiscover;
   int* IsFinish;
   int* IsColor;
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
   G->IsDiscover = calloc(n+1, sizeof(int));
   assert(G->IsDiscover!=NULL);
   G->IsFinish = calloc(n+1, sizeof(int));
   assert(G->IsFinish!=NULL);
   G->IsColor = calloc(n+1, sizeof(int));
   assert(G->IsColor!=NULL);
   G->sizeNumE = 0;
   G->orderNumV = n;
   for(int i=1; i<(n+1); i++){
      G->IsAdjList[i] = newList();
	  G->IsParent[i] = NIL;
	  G->IsDiscover[i] = UNDEF;
      G->IsFinish[i] = UNDEF;
	  G->IsColor[i] = 4;
   }
   return G;
}

// freeGraph()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph* pG){
   if( pG!=NULL && *pG!=NULL ){
	  for(int i=1; i<((*pG)->orderNumV+1); i++){
	     freeList(&((*pG)->IsAdjList[i]));
	  }
      free((*pG)->IsAdjList);
	  free((*pG)->IsColor);
	  free((*pG)->IsParent);
	  free((*pG)->IsDiscover);
	  free((*pG)->IsFinish);
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

// getParent()
// Returns u's parent vertex in DFS Tree
// NIL if DFS() not yet called
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getParent() w/ vertex 'u' out of bounds\n");
      exit(1);
   }
   return G->IsParent[u];
}

// getDiscover()
// Returns discover time of a vertex u
// NIL if DFS() not yet called
// Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getDiscover() w/ vertex 'u' out of bounds\n");
      exit(1);
   }
   return G->IsDiscover[u];
}

 getFinish()
// Returns finish time of a vertex u
// UNDEF if DFS() not yet called
// Pre: 1 <= u <= getOrder(G)
void getFinish(Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getFinish() w/ vertex 'u' out of bounds\n");
      exit(1);
   }
   return G->IsFinish[u];
}

// Manipulation procedures ----------------------------------------------------

// makeNull()
// Resets Graph to its original (no edge) state
void makeNull(Graph G){
   for(int i=1; i<(getOrder(G)+1); i++){
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
	  addArc(G, v, u); // What is an edge? but two directed edges (two arcs)
	  addArc(G, u, v);
	  G->sizeNumE--; // We must account for the two size++. As this is just one edge
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
   }else{ // List is empty. We must use append to avoid the moveFront() on empty list error
	  moveFront(L);
      while( v > get(L) && index(L)!= -1){ //while we are on the list and v is greater than current entry
         moveNext(L);
      }
      if(index(L) == -1){ // We've fallen off the list.
         append(L, v);
      }else{ // We didn't fall off the list. v belongs before the current element.
        insertBefore(L, v);
      }
   }
   G->sizeNumE++;
}

// DFS_Visit()
// Helper function to DFS. 
// Reaches all the vertices on u's adjList before returning to DFS
void DFS_Visit(Graph G, List S, int u, int *time){
   *time++;
   G->IsDiscover[u] = *time;
   G->IsColor[u] = 5;
   moveFront(G->IsAdjList[u]);
   int current = get(G->IsAdjList[u]);
   while(index(G->IsAdjList[current]) != -1){ // Process adjList
      int v = get(G->IsAdjList[current]);
      if(G->IsColor[v] == 4){
         G->IsParent[v] = u;
         DFS_Visit(G, S, v, time);
         }
		moveNext(G->IsAdjList[current]); 
      }
	  G->IsColor[v] = 6;
	  *time++;
      G->IsFinish[u] = *time;
	  insertAfter(S, u);
}// Remember our convention: IsColor =>{white= 4, grey = 5, black = 6}

// DFS()
// Inserts a new edge into the graph
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S){
   if(length(S) != getOrder(G)){
      printf("Graph Error: calling DFS() on a graph and list with different numVertices\n");
      exit(1);
   }
   for(int i=1; i<(G->orderNumV + 1); i++){ //If you call DFS more than
      G->IsParent[i] = NIL; // once it is necessary to reset the
	  G->IsDiscover[i] = UNDEF; // values for the algorithm to run
	  G->IsFinish[i] = UNDEF; // first runtime is the trivial case
	  G->IsColor[i] = 4; // and this for loop is redundant.
   } // Time is local to DFS we will pass its address to visit.
   int time = 0; // This is option two in the project description.
   moveBack(S); // S is a list that is a two part stack.
   while(index(S) == G->orderNumV){ // first controls the list. index(S) = numV
      int u = front(S);
	  if(G->IsColor[v] == 4){
	     DFS_Visit(G, S, u, &time);
	  }
	  deleteFront(S);
   }
}

// Other Functions ------------------------------------------------------------

// transpose()
// Returns the transpose of this graph
// This algorithm is much simpler for the computer than to do by hand.
// I wrote insertAfter/Before() in list based on insertion sort so all
// lists even the adjList of transpose are necessarily in sorted order.
Graph transpose (Graph G){
   Graph transpose = newGraph(getOrder(G));
   for(int i = 1; i<(getOrder(G)+1); i++){ // Loop through each adjList[i] in G
      moveFront(G->IsAdjList[i]);
	  int current = get(G->IsAdjList[i]);
      while(index(G->IsAdjList[current]) != -1){ // Loop through each List element
	     addArc(transpose, current, i); // Just like transpose in pa3
		 moveNext(G->IsAdjList[i]);
	  }
   }
   return transpose;
}

// copyGraph()
// returns a new Graph with the same entries as this Graph
Graph copyGraph(Graph G){
   Graph copy = newGraph(getOrder(G));
   for(int i = 1; i<(getOrder(G)+1); i++) {
      if(isEmpty(G->IsAdjList[i])){
      //do nothing
      }else{
      //System.out.println(i); //for debugging...
      copy->IsAdjList[i] = G->IsAdjList[i];
      copy->IsParent[i] = G->IsParent[i];
      copy->IsDiscover[i] = G->IsDiscover[i];
      copy->IsFinish[i] = G->IsFinish[i];
      copy->IsColor[i] = G->IsColor[i];
      }
   }
   return copy;
}

// printGraph()
// Prints data elements in G on a single line to stdout.
void printGraph(FILE* out, Graph G){
   if(out == NULL || G == NULL){
      printf("Graph Error: called printGraph() on a null reference\n");
      exit(1);
   }
   for(int i = 1; i<(getOrder(G)+1); i++){
      fprintf(out, "%d: ", i);
      printList(out, G->IsAdjList[i]);
      fprintf(out, "\n");
   }
}
