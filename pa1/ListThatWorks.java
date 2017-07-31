/*	Nicholas Pappas
	nhpappas@ucsc.edu
	ID: 1558554
	CMPS 101 w/ Tantalo MWF 10:40-11:45AM
	Assignment: pa1
*/
//-----------------------------------------------------------------------------
//  List.java
//  A List ADT
//-----------------------------------------------------------------------------

class List{

   private class Node{
      // Fields
      int data;
      Node next;
	  Node prev;
      
      // Constructor
      Node(int data) { this.data = data; next = null; prev = null; }
      
      // toString():  overrides Object's toString() method
      public String toString() { 
         return String.valueOf(data); 
      }
      
      // equals(): overrides Object's equals() method
      public boolean equals(Object x){
         boolean eq = false;
         Node that;
         if(x instanceof Node){
            that = (Node) x;
            eq = (this.data== that.data);
         }
         return eq;
      }
   }

   // Fields
   
   private Node back;
   private Node cursor;
   private Node front;
   private int index;
   private int length;

   // Constructor
   List() { 
      front = back = cursor = null; 
      length = 0; 
	  index = -1;
   }

// Access Functions --------------------------------------------------------

   // isEmpty()
   // Returns true if this List is empty, false otherwise.
   boolean isEmpty() { 
      return length==0; 
   }

   // length()
   // Returns the number of elements in this List.
   int length() { 
      return length; 
   }
   
   // index()
   // If cursor is defined, returns the index of the cursor element,
   // otherwise returns -1.
   int index() { 
      return index; 
   }
   
   // front() 
   // Returns front element. 
   // Pre: length()>0
   Node front(){
      if( this.isEmpty() ){
         throw new RuntimeException(
            "List Error: front() called on empty List");
      }
      return front;
   }
   
   // back() 
   // Returns back element. Pre: length()>0
   // Pre: length()>0
   Node back(){
      if( this.isEmpty() ){
         throw new RuntimeException(
            "List Error: back() called on empty List");
      }
      return back;
   }
   
   // get() 
   // Returns cursor element.
   // Pre: length()>0, index()>=0
   Node get(){
      if( this.isEmpty() ){
         throw new RuntimeException(
            "List Error: get() called on empty List");
      }
      return cursor;
   }
   
   // equals()
   // Returns true if this List and L are the same integer
   // sequence. The cursor is ignored in both lists.
   boolean equals(List L){
      boolean eq  = false;
      List Q;
      Node N, M;

      if(L instanceof List){
         Q = (List)L;
         N = this.front;
         M = Q.front;
         eq = (this.length==Q.length);
         while( eq && N!=null ){
            eq = N.equals(M);
            N = N.next;
            M = M.next;
         }
      }
      return eq;
   }
  

   // Manipulation Procedures -------------------------------------------------

   // clear()
   // Resets this List to its original empty state.
   void clear(){
      front = back = cursor = null; 
      length = 0; 
	  index = -1;
   }
   
   // moveFront()
   // If List is non-empty, places the cursor under the front element,
   // otherwise does nothing.
   void moveFront(){
	  if( this.isEmpty() ){
         throw new RuntimeException(
            "List Error: moveFront() called on empty List");
      }
	  index = length;
	  cursor = front;
   }
   
   // moveBack()
   // If List is non-empty, places the cursor under the back element,
   // otherwise does nothing.
   void moveBack(){
	  if( this.isEmpty() ){
         throw new RuntimeException(
            "List Error: moveBack() called on empty List");
      }
	  index = 0;
	  cursor = back;
   }
   
   // movePrev()
   // If cursor is defined and not at back, moves cursor one step toward 
   // back of this List, if cursor is defined and at back, cursor becomes
   // undefined, if cursor is undefined does nothing.
   void movePrev(){
	  if( this.isEmpty() ){
         throw new RuntimeException(
            "List Error: movePrev() called on empty List");
      }
	  if(index == -1 || index == 0){
		 index = -1;
      }
	  else{
		 index--;
	     cursor = cursor.prev;
	  }
   }
   
   // moveNext()
   // If cursor is defined and not at front, moves cursor one step toward
   // front of this List, if cursor is defined and at front, cursor becomes
   // undefined, if cursor is undefined does nothing.
   void moveNext(){
	  if( this.isEmpty() ){
         throw new RuntimeException(
            "List Error: moveNext() called on empty List");
      }
	  if(index == -1 || index == length){ //undefined does nothing || walks off list
		 index = -1;
      }
	  else{
		 index++;
	     cursor = cursor.next;
	  }
   }
   
   // prepend() 
   // Insert new element into this List.  If List is non-empty, 
   // insertion takes place before back element.
   void prepend(int data){
      if( this.isEmpty() ){
         front = back = cursor = new Node(data);
		 length++;
		 index = 1;
      }
	  else{
		 Node temp = new Node(data);
		 back.prev = temp;
		 temp.next = back;
		 back = temp;
		 length++;
		 index++;
		}
   }
   
   // append()
   // Insert new element into this List.  If List is non-empty, 
   // insertion takes place after front element.
   void append(int data){
      if( this.isEmpty() ){
         front = back = cursor = new Node(data);
		 length++;
		 index = 1;
      }
	  else{
		 Node temp = new Node(data);
		 front.next = temp;
		 temp.prev = front;
		 front = temp;
		 length++;
	  }
   }

   // insertBefore()
   // Insert new element before cursor.
   // Pre: length()>0, index() >=0
   void insertBefore(int data){
	  if( this.isEmpty() ){
         throw new RuntimeException(
            "List Error: insertBefore() called on empty List");
      }
	  if( this.index == -1){
         throw new RuntimeException(
            "List Error: insertBefore() called on nullCursor");
	  }
	  
	  Node temp;
	  
	  temp = cursor.prev;
	  temp.next = new Node(data);
	  temp.next.next = cursor;
	  length++; index++;
	  
   }
   
   // insertAfter()
   // Insert new element after cursor.
   // Pre: length()>0, index() >=0
   void insertAfter(int data){
	  if( this.isEmpty() ){
         throw new RuntimeException(
            "List Error: insertAfter() called on empty List");
      }
	  if( this.index == -1){
         throw new RuntimeException(
            "List Error: insertAfter() called on nullCursor");
	  }
	  
	  cursor.next = new Node(data);
	  cursor = cursor.next;
	  length++; index--;
   }

   
   // deleteFront()
   // Deletes front element from this List.
   // Pre: length()>0
   void deleteFront(){
      if(this.isEmpty()){
         throw new RuntimeException(
            "List Error: deleteFront() called on empty List");
      }
	  if (index == length){
		  front = front.prev;
		  index = -1;
	  }
      if(this.length>1){
         front = front.prev;
      }else{
         front = back = null;
      }
	  
      length--;
   }
   
   // deleteBack()
   // Deletes back element from this List.
   // Pre: length()>0
   void deleteBack(){
      if(this.isEmpty()){
         throw new RuntimeException(
            "List Error: deleteBack() called on empty List");
      }
	  if (index == 0){
		  back = back.next;
		  index = -1;
	  }
      if(this.length>1){
         back = back.next;
      }else{
         front = back = null;
      }
      length--;
	  index--;
   }

   // delete()
   // Deletes cursor element, making cursor undefined.
   // Pre: length()>0, index()>=0
   void delete(){
      if(this.isEmpty()){
         throw new RuntimeException(
            "List Error: delete() called on empty List");
      }
      if(this.length>2){
         cursor = cursor.prev;
		 cursor.next = cursor.next.next;
		 index = -1;
      }else if(this.length == 2){
		 cursor = null;
		 index = -1;
	  }else{
		 front = back = cursor = null; 
		 index = -1;
      }
      length--;
   }
   
   // Other Functions ---------------------------------------------------------

   // toString()
   // Overides Object's toString() method.
   public String toString(){
      StringBuffer sb = new StringBuffer();
      Node N = back;
      while(N!=null){
         sb.append(" ");
         sb.append(N.toString());
         N = N.next;
      }
      return new String(sb);
   }

   // copy()
   // Returns a new List identical to this List.
   List copy(){
      List L = new List();
      Node N = this.back;

      while( N!=null ){
         L.append(N.data);
         N = N.next;
      }
      return L;
   }

}