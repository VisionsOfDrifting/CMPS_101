/*	Nicholas Pappas
	nhpappas@ucsc.edu
	ID: 1558554
	Assignment: pa5
*/
#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"

int main(void){
   Dictionary D = newDictionary();
   
   insert(D,"50","12"); //Note that if you pass "50" and "12" as type int causes segfault
   insert(D,"12","12");
   insert(D,"34","2");
   insert(D,"23","1");
   insert(D,"68","15");
   insert(D,"lastOne","16");
   printDictionary(stdout,D);
   
   delete(D,"50");
   delete(D,"23");
   delete(D,"lastOne");
   
   printDictionary(stdout,D);
   	
   makeEmpty(D);
   freeDictionary(&D);
   //printDictionary(stdout,D);

}