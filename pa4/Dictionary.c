/*	Nicholas Pappas
	nhpappas@ucsc.edu
	ID: 1558554
	Assignment: pa5
*/
//-----------------------------------------------------------------------------
//   Dictionary.c
//   Implementation file for Dictionary ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"


// private types --------------------------------------------------------------
const int tableSize=101;

// NodeObj
typedef struct NodeObj{
   char* p;
   char* value;
   struct NodeObj* next;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// constructor of the Node type
Node newNode(char* x, char* y) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->p = x;
   N->value = y;
   N->next = NULL;
   return(N);
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}
/* May need to insert list obj into array to insert at the head
// ListObj
typedef struct ListObj{
   char* p;
   char* value;
   struct ListObj* next;
} ListObj;

// List
typedef ListObj* List;

// newList()
// constructor of the List type
List newList(char* x, char* y) {
   List N = malloc(sizeof(ListObj));
   assert(N!=NULL);
   N->p = x;
   N->value = y;
   N->next = NULL;
   return(N);
}

// freeList()
// destructor for the List type
void freeList(List* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}*/

// DictionaryObj
// Exported reference type
typedef struct DictionaryObj{
   Node* table;
   int numPairs;
} DictionaryObj;

typedef struct DictionaryObj* Dictionary;

// public functions -----------------------------------------------------------

// newDictionary()
// constructor for the Dictionary type
Dictionary newDictionary(void){
   Dictionary D = malloc(sizeof(DictionaryObj));
   assert(D!=NULL);
   D->table = calloc(tableSize, sizeof(Node));
   assert(D->table!=NULL);
   D->numPairs = 0;
   return D;
}

// freeDictionary()
// destructor for the Dictionary type
void freeDictionary(Dictionary* pD){
   if( pD!=NULL && *pD!=NULL ){
      if( !isEmpty(*pD) ) makeEmpty(*pD);
      free((*pD)->table);
	  free(*pD);
      *pD = NULL;
   }
}

// isEmpty()
// returns 1 (true) if D is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D){
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: calling isEmpty() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return(D->numPairs==0);
}

// size()
// pre: none
// post: returns the number of entries in this Dictionary
int size(Dictionary D) {
	return D->numPairs;
	}
	
// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
	int sizeInBits = 8*sizeof(unsigned int);
	shift = shift & (sizeInBits-1);
	if ( shift == 0 ){
		return value;}
	else{
		return(value << shift) | (value >> (sizeInBits-shift));
	}
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) { 
	unsigned int result = 0xBAE86554;
	while (*input) { 
		result ^= *input++;
		result = rotate_left(result, 5);
		}
	return result;
	}

//This is the one you actually call
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
	return pre_hash(key)%tableSize;
	}

// findKey()
// returns a reference to the Node with this key in this Dictionary
Node findKey(Dictionary D, char* k){
    Node N;
    if( D==NULL ){
      fprintf(stderr, "Dictionary Error: calling findKey() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
	}
	
	N = D->table[hash(k)];
	while(N != NULL){
		if(strcmp(N->p,k)== 0){
			break;}
		else{
			N = N->next;
			}
		}
	return N;
	}

// lookup()
// returns the value v such that (k, v) is in D, or returns NULL if no 
// such value v exists.
// pre: none
char* lookup(Dictionary D, char* k){
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
    }
   if(findKey(D, k)!= NULL){
	  return findKey(D, k)->value;}
   else{
	  return NULL;
	}
}

// insert()
// inserts new (key,value) pair into D
// pre: lookup(D, k)==NULL
void insert(Dictionary D, char* k, char* v){
   Node N;
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: calling insert() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if( findKey(D,k)!=NULL ){
      fprintf(stderr, "insert(): cannot insert duplicate keys\n");
      exit(EXIT_FAILURE);
   }
   int h = hash(k);
   if(D->table[h] == NULL){
		D->table[h] = newNode(k,v);
	 }
   else {
		N = newNode(k, v);
		N->next = D->table[h];
		D->table[h] = N;
	 }
	D->numPairs++;
}

// delete()
// deletes pair with the key k
// pre: lookup(D, k)!=NULL
void delete(Dictionary D, char* k){
   Node M;
   Node N;
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: calling delete() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if( D->numPairs==0 ){
      fprintf(stderr, "Dictionary Error: calling delete() on empty Dictionary\n");
      exit(EXIT_FAILURE);
   }
  
   if( findKey(D,k) == NULL ){
      fprintf(stderr, "delete(): cannot delete non-existent key \n");
      exit(EXIT_FAILURE);
    }
	
	N = findKey(D,k);
   if(N == D->table[hash(k)] && N->next == NULL){ //delete head w/ only one value in table slot
      freeNode(&N);
	  D->table[hash(k)] = NULL;
   }else if(N == D->table[hash(k)]){ //delete head w/ more than one value in table slot
      D->table[hash(k)] = N->next;
      freeNode(&N);
   }else{
      M = D->table[hash(k)];
      while(M->next != N){
         M = M->next;
      }
      if(N->next == NULL){ //delete tail
		M->next = NULL;
		freeNode(&N);
		}
	  M->next = N->next; //delete middle
      freeNode(&N);
	}
   D->numPairs--;
   
}

// makeEmpty()
// resets D to the empty state
// pre: !isEmpty(D)
void makeEmpty(Dictionary D){
	Node N;
	if(D==NULL)
	{
		fprintf(stderr,"Dictionary Error: calling makeEmpty() on NULL Dictionary reference");
		exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < tableSize; i++){ //searching through 0 to tableSize
		while(D->table[i] != NULL){ //while the current node is not free
			N = D->table[i];
			D->table[i] = N->next;
			freeNode(&N);
			N = NULL;
		}
	}
	D->numPairs=0;
}

// printDictionary()
// prints a text representation of D to the file pointed to by out
// pre: none
void printDictionary(FILE* out, Dictionary D){
   Node N;
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
	for(int i = 0; i < tableSize; i++){ //searching through 0 to tableSize
		N = D->table[i];
		while(N != NULL){ //while the current node is not free
			fprintf(out, "%s %s\n", N->p, N->value );
			N = N->next;
		}
	}
}