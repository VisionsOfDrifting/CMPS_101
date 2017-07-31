/*	Nicholas Pappas
	nhpappas@ucsc.edu
	ID: 1558554
	CMPS 101 w/ Tantalo MWF 10:40-11:45AM
	Assignment: pa3
*/
//-----------------------------------------------------------------------------
//  Matrix.java
//  A Matrix ADT with inner class Entry
//-----------------------------------------------------------------------------

class Matrix{

   private class Entry{
      // Fields
	  int column;
      double value;
      
      // Constructor
      Entry(int column, double value) { 
		 this.column = column;
         this.value = value;}
      
      // toString():  overrides Object's toString() method
      public String toString() { 
         String s = column + " " + value; 
		 return s;
      }
      
      // equals(): overrides Object's equals() method
      public boolean equals(Object x){
         boolean eq = false;
         Entry that;
         if(x instanceof Entry){
            that = (Entry) x;
            eq = (this.value== that.value);
         }
         return eq;
      }
   }

   // Fields
   
   private int length;
   private List[] row;
   // Constructor
   // Do note that the Matrix ADT starts at row 0, column 0. Matricies begin at 1, 1.
   Matrix(int n) { 
      row = new List[n];
	  for(int i = 0; i < n ; i++){
          row[i] = new List();
      }
	  length = n;
   }

// Access Functions --------------------------------------------------------
   
   //int getSize() // Returns n, the number of rows and columns of this Matrix
  // int getNNZ() // Returns the number of non-zero entries in this Matrix
   
   // equals()
   // Returns true if this Matrix and L are the same integer
   // sequence. The cursor is ignored in both lists.
   /*boolean equals(Object x){
      boolean eq  = false;
      Matrix Q;
      Entry N, M;

      if(x instanceof Matrix){
         Q = (Matrix)x;
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
  */

   // Manipulation Procedures -------------------------------------------------

   // makeZero()
   // Sets this Matrix to the zero state.
   void makeZero(){
	   for(int i = 0; i < n ; i++){
          row[i].clear();
      }
   }
   
   // copy()
   // returns a new Matrix having the same entries as this Matrix
   Matrix copy(){
      Matrix copy = new Matrix(this.length);
	  for(int i = 0; i < n ; i++){
         copy.row[i] = this.row[i];
      }
	  return copy;
   }
   
   // changeEntry(int i, int j, double x)
   // changes ith row, jth column of this Matrix to x
   // pre: 1<=i<=getSize(), 1<=j<=getSize()
   void changeEntry(int i, int j, double x){
      row[i].moveFront();
	  outerloop:
	  while(row[i].get() != null){
		 
		 Entry E = (Entry)row[i].get();
		  if(E.column == j){
			  if(x == 0){
                 row[i].delete();
			  }else{ //x!=0 we must overwrite its value
			     E.value = x;
			  }
			  break outerloop;
		  }
		  if(j > E.column){
		     row[i].moveNext();
		  }
		  if(row[i].index() == -1){
			  if(x != 0){
				  Entry Mij = new Entry(j, x);
				  row[i].append(Mij);
			  }			  
			  break outerloop;
		  }
		  if(j < E.column){
			  Entry Mij = new Entry(j, x);
			  row[i].insertBefore(Mij);
		  }
	  }
   }
   
   // scalarMult(double x)
   // returns a new Matrix that is the scalar product of this Matrix with x
   Matrix scalarMult(double x){
	   Matrix product = new Matrix(this.length);
	   for(int i = 0; i < this.length ; i++){
         while(product.row[i].index() != null){
		    Entry E = (Entry)row[i].get();
			int y = E.value * x;
			product.changeEntry(i, E.column, y);
			product.row[i].moveNext();
		 }
      }
   }
   
   /*
   // add(Matrix M)
   // returns a new Matrix that is the sum of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix add(Matrix M){
	   
   }
   
   Matrix sub(Matrix M)
   // returns a new Matrix that is the difference of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix transpose()
   // returns a new Matrix that is the transpose of this Matrix
   Matrix mult(Matrix M)
   // returns a new Matrix that is the product of this Matrix with M
   // pre: getSize()==M.getSize()
   */
   // Other Functions ---------------------------------------------------------
/*
   // toString()
   // Overides Object's toString() method.
   public String toString(){
      StringBuffer sb = new StringBuffer();
      Entry N = front;
      while(N!=null){
         sb.append(" ");
         sb.append(N.toString());
         N = N.next;
      }
      return new String(sb);
   }
*/
}