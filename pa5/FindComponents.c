/****************************************************************************************
*  Nicholas Pappas
*  nhpappas@ucsc.edu
*  CMPS 101 w/ Tantalo
*  Assignment: pa5
*****************************************************************************************/
//-----------------------------------------------------------------------------
// FindComponents.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
// Uses the Graph ADT to implement DFS and find SCC's in the input file.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Graph.h"

#define MAX_LEN 400

int main(int argc, char * argv[]){
   FILE *in, *out;
   char line[MAX_LEN];
   int size = 0;
   int SCCs = 0;
   
   if( argc != 3 ){
      printf("FindComponents: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   fgets(line, MAX_LEN, in); // Reads in the 1st line (size of graph).
   sscanf(line, "%d", &size); // Use a parseint() to get the size.
   Graph G = newGraph(size); // Create the graph.
   List S = newList(); // This is the stack. It is not initialized in Graph.c
   for(int i = 1; i < (size + 1); i++){ // S is two parts, indices and a stack.
      append(S,i); // Here we fill in the indices.
   }
   
   while(fgets(line, MAX_LEN, in) != NULL) { // Reads in all the pairs into the graph.
      int a = 0, b = 0;
      sscanf(line, "%d %d", &a, &b);
      if(a != 0 && b != 0){ // If a && b !=0 then they are vertices and represent an edge.
         addArc(G, a, b);
	  }else{ // The end pair (0, 0).
		  break;
	  }
   }
   
   // This is the algorithm given to find strongly connected components
   DFS(G, S); // Here S acts as indices we pop them off the front and push onto the stack.
   Graph T = transpose(G);
   DFS(T, S); // Here S is in the order of finish times as a stack.
   moveFront(S); // The state of S after DFS runs again contains the SCCs.
   while(index(S) != -1){
      if(getParent(T, get(S)) == NIL){ // Note num SCC corresponds
	     SCCs++; // to num trees, each of which has a NIL parent.
	  }
	  moveNext(S);
   }
   
   List component[SCCs]; 
   for(int i = 0; i < SCCs; i++) { // Allocate a list for each component.
      component[i] = newList();
   }
   
   moveFront(S);
   int temp = SCCs;
   while(index(S) != -1) { // Load the components into the corresponding lists.
      if(getParent(T, get(S)) == NIL){
         temp--;
      }
      append(component[temp], get(S));
      moveNext(S);		 
   }

   // Matching the given output...
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);
   fprintf(out, "\nG contains %d strongly connected components:", SCCs);
   for(int i = 0; i < SCCs; i++) {
      fprintf(out, "\nComponent %d: ", (i + 1));
      printList(out, component[i]);
      freeList(&(component[i]));
   }
   
   fprintf(out, "\n"); // Free memory close files, end of program.
   freeGraph(&T);
   freeList(&S);
   freeGraph(&G);
   fclose(in);
   fclose(out);
   return(0);
}