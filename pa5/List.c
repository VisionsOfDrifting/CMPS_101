/****************************************************************************************
*  Nicholas Pappas
*  nhpappas@ucsc.edu
*  CMPS 101 w/ Tantalo
*  Assignment: pa5
*****************************************************************************************/
//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
	  while(!isEmpty(*pL)){ 
         deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}

// index()
// Returns the index of L.
int index(List L){
   if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return(L->index);
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }
   return(L->back->data);
}

// get()
// Returns the value at the cursor of L.
// Pre: !isEmpty(L)
int get(List L){
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling get() on an empty List\n");
      exit(1);
   }
   return(L->cursor->data);
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return(eq);
}

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   return(L->length==0);
}


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets this List to its original empty state.
void clear(List L){
   while( !isEmpty(L) ) { 
      deleteFront(L); 
   }
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
}

// moveFront()
// If List is non-empty, places the cursor under the front element, //back element
// otherwise does nothing.
void moveFront(List L){
   if( isEmpty(L) ) {
      printf("List Error: moveFront() called on empty List");
      exit(1);
   }
   L->index = 0;
   L->cursor = L->front;
}

// moveBack()
// If List is non-empty, places the cursor under the back element, //front element
// otherwise does nothing.
void moveBack(List L){
   if( isEmpty(L) ) {
      printf("List Error: moveBack() called on empty List");
      exit(1);
   }
   L->index = (L->length - 1);
   L->cursor = L->back;
}

// movePrev()
// If cursor is defined and not at back, moves cursor one step toward 
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L){
   if( isEmpty(L) ) {
      printf("List Error: movePrev() called on empty List");
      exit(1);
   }
   if( L->index == -1 || L->index == 0 ) {
	   L->index = -1;
   }else{
      L->index--;
      L->cursor = L->cursor->prev;
   }
}

// moveNext()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L){
   if( isEmpty(L) ) {
      printf("List Error: movenext() called on empty List");
      exit(1);
   }
   if( L->index == -1 || L->index == (L->length - 1) ){
	   L->index = -1;
   }else{
      L->index++;
      L->cursor = L->cursor->next;
   }
}

// append() 
// Insert new element into this List.  If List is non-empty, 
// insertion takes place before back element.
void append(List L, int data){
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ) { 
      L->front = L->back = L->cursor = N; 
	  L->length++;
	  L->index = 0;
   }else{ 
      L->back->next = N; 
      N->prev = L->back;
	  L->back = N; 
	  L->length++;
   }
}

// prepend()
// Insert new element into this List.  If List is non-empty, 
// insertion takes place after front element.
void prepend(List L, int data){
	Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ) { 
      L->front = L->back = L->cursor = N; 
	  L->length++;
	  L->index = 0;
   }else{ 
      L->front->prev = N; 
      N->next = L->front;
	  L->front = N; 
	  L->length++;
      L->index++;
   }
}
// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index() >=0
void insertBefore(List L, int data){
   if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ) { 
      printf("List Error: insertBefore() called on empty List");
      exit(1);
   }
   if( L->index == -1 ) { 
      printf("List Error: insertBefore() called on nullCursor");
      exit(1);
   }
   
   if( L->index > 0){
      Node N = newNode(data);
      Node temp = L->cursor->prev;
      N->next = L->cursor;
      N->prev = temp;
      L->cursor->prev = N;
      temp->next = N;
	  L->length++;
      L->index++;
   }else{
	   prepend(L, data);
   }
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index() >=0
void insertAfter(List L, int data){
	
   if( L==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ) { 
      printf("List Error: insertAfter() called on empty List");
      exit(1);
   }
   if( L->index == -1 ) { 
      printf("List Error: insertAfter() called on nullCursor");
      exit(1);
   }
   
   if( L->index == L->length-1 ){
      append(L, data);
   }else{
	  Node N = newNode(data);
      Node temp = L->cursor->next;
      N->prev = L->cursor;
      N->next = temp;
      temp->prev = N;
      L->cursor->next = N;
      L->length++;
   }
}

// deleteFront()
// Deletes front element from this List.
// Pre: length()>0
void deleteFront(List L){
   Node N = NULL;
   Node temp = NULL;
   if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteFront on an empty List\n");
      exit(1);
   }
   N = L->front;
   if(L->cursor == N){
      L->cursor = NULL;
      L->index = -1;
   }
   if(length(L) > 1){
      temp = N->next;
      temp->prev = NULL;
      L->front = temp;
      if(L->index > 0){
	  L->index--;
      }
   }else{
     L->front = L->back = L->cursor = NULL;
     L->index = -1;
   }
   freeNode(&N);
   L->length--;
}

// deleteBack()
// Deletes back element from this List.
// Pre: length()>0
void deleteBack(List L){
   Node N = NULL;
   Node temp = NULL;
   if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteFront on an empty List\n");
      exit(1);
   }
   N = L->back;
   if(L->cursor == N){
      L->cursor = NULL; 
      L->index = -1;
   }
   if(length(L) > 1){
      temp = N->prev;
      temp->next = NULL;
      L->back = temp;
   }else{
     L->front = L->back = L->cursor = NULL;
     L->index = -1;
   }
   freeNode(&N);
   L->length--;
}

// delete()
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
   Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteFront on an empty List\n");
      exit(1);
   }
   N = L->cursor;
   if(N == L->front){
      deleteFront(L);
   }else if(N == L->back){
      deleteBack(L);
   }else { 
      Node temp = N->next;
      L->cursor = L->cursor->prev;
	  L->cursor->next = temp;
	  temp->prev = L->cursor;
	  L->index = -1;
   }
   L->length--;
   freeNode(&N);
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }

   for(N = L->front; N != NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
}

// copyList()
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L){
   List C = newList();
   Node N = NULL;
   for(N = L->front; N != NULL; N = N->next){
      append(C, N->data);
   }
   return(C);
}
