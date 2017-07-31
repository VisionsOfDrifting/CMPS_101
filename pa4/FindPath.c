/****************************************************************************************
*  Nicholas Lappas
*  nhpappas@ucsc.edu
*  CMLS 101 w/ Tantalo
*  Assignment: pa4
*****************************************************************************************/
//-----------------------------------------------------------------------------
// FindLath.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
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
   
   if( argc != 3 ){
      printf("FindLath: %s <input file> <output file>\n", argv[0]);
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

   fgets(line, MAX_LEN, in); //reads in the first line (size of graph).
   sscanf(line, "%d", &size); //parseint()
   Graph G = newGraph(size); //create the graph
   
   while(fgets(line, MAX_LEN, in) != NULL) { //reads in all the pairs into the graph
      int a = 0, b = 0;
      sscanf(line, "%d %d", &a, &b);
      if(a != 0 && b != 0){ //if a && b !=0 then they are verticies and represent an edge
         addEdge(G, a, b);
	  }else{ //the end pair (0, 0)
		  break;
	  }
   }
   printGraph(out, G); //prints adjacencyList
   
   //Now we load the second part of the in file. We call BFS to find the shortest paths.
   while(fgets(line, MAX_LEN, in) != NULL){
      int a = 0, b = 0;
      sscanf(line, "%d %d", &a, &b); //Get verticies to compare
      if(a != 0 && b != 0){
         fprintf(out, "\n");
         BFS(G, a); //Use BFS to find the shortest distance
         int dist = getDist(G, b); //store it
         fprintf(out, "The distance from %d to %d is ", a, b);
         if(dist == INF){
            fprintf(out, "infinity\n");
		 }
         else{
            fprintf(out, "%d\n", dist);
		 }
		 
         List L = newList();
         getPath(L, G, b); //Use getPath to find the verticies in the shortest path
         if(front(L) == NIL){
            fprintf(out, "No %d-%d path exists", a, b);
		 }
         else {
            fprintf(out, "A shortest %d-%d path is: ", a, b);
		    printList(out, L);
		 }
		 freeList(&L);
	  }else{ //again the end is marked by pair (0, 0)
		  break;
	  }
   }
   
   fprintf(out, "\n"); //Free memory close files, end of program
   freeGraph(&G);   
   fclose(in);
   fclose(out);
   return(0);
}