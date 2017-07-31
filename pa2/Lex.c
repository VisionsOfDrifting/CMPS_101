/****************************************************************************************
*  Nicholas Pappas
*  nhpappas@ucsc.edu
*  CMPS 101 w/ Tantalo
*  Assignment: pa1
*****************************************************************************************/
//-----------------------------------------------------------------------------
// Lex.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 400

int main(int argc, char * argv[]){

   int i, n=0, count=0;
   FILE *in, *out;
   char line[MAX_LEN];

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
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

   List A = newList();
   /* read each line of input file, & count num lines*/
   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
   }
   //close and open the infile
   fclose(in);
   in = fopen(argv[1], "r");
   
      char word[count-1][MAX_LEN];
   /* read lines into word[]*/
    n=0;
   while( fgets(line, MAX_LEN, in) != NULL)  {
      //printf("%s",line);
      strcpy(word[n],line);
      n++;
   }
   //printf("File input done\n");
   append(A, 0);
   /*for(i=0; i<count; i++){
        printf("%s\n",word[i]);
    }*/
   for (i= 1; i<count; i++){
	   moveFront(A);
	   while(index(A) != -1){
          // printf("%s",word[i]);
		   if( strcmp(word[i], word[get(A)]) < 0 ){
		   //s1.compareTo(s2)<0 is true if and only if s1 comes before s2
		      insertBefore(A, i);
		      break;
		   }else{
			  moveNext(A);
		   }
		   
		   if(index(A) == -1){
              append(A, i);
              break;
		   }
	   }
   }
   moveFront(A);
   while( index(A) != -1 ){
	   fprintf(out, "%s", word[get(A)]);
	   moveNext(A);
   }
   freeList(&A);
   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}