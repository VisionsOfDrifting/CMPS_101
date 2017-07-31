#	Nicholas Pappas
#	nhpappas@ucsc.edu
#	ID: 1558554
#	Assignment: pa1
#
#------------------------------------------------------------------------------
#
#  Makefile for CMPS 101 pa1 
#  Compiles all .java files in the current directory and creates an executable
#  jar file called Lex.  See the following for a short description of makefiles
#
#       https://classes.soe.ucsc.edu/cmps012b/Summer15/lab1.pdf
#
#------------------------------------------------------------------------------ 

MAINCLASS  = Lex
JAVAC      = javac 
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) Makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS)
SUBMIT	   = submit cmps101-pt.f16 pa1

all: $(JARFILE)
	
$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class $(JARFILE)

submit: $(SOURCES)
	$(SUBMIT) $(SOURCES)