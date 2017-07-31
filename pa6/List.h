/****************************************************************************************
*  Nicholas Pappas
*  nhpappas@ucsc.edu
*  CMPS 101 w/ Tantalo
*  Assignment: pa6
*****************************************************************************************/
//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L);

// index()
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int index(List L);

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L);

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L);

// get()
// Returns the value at the get of L.
// Pre: !isEmpty(L)
int get(List L);

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B);

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L);


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets this List to its original empty state.
void clear(List L);

// moveFront()
// If List is non-empty, places the cursor under the front element, //back element
// otherwise does nothing.
void moveFront(List L);

// moveBack()
// If List is non-empty, places the cursor under the back element, //front element
// otherwise does nothing.
void moveBack(List L);

// movePrev()
// If cursor is defined and not at back, moves cursor one step toward 
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L);

// moveNext()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L);

// prepend() 
// Insert new element into this List.  If List is non-empty, 
// insertion takes place before back element.
void prepend(List L, int data);

// append()
// Insert new element into this List.  If List is non-empty, 
// insertion takes place after front element.
void append(List L, int data);

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index() >=0
void insertBefore(List L, int data);

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index() >=0
void insertAfter(List L, int data);

// deleteFront()
// Deletes front element from this List.
// Pre: length()>0
void deleteFront(List L);

// deleteBack()
// Deletes back element from this List.
// Pre: length()>0
void deleteBack(List L);

// delete()
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L);

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L);

// copyList()
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L);

#endif
