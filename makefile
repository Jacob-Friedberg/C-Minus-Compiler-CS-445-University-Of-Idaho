# MakeFile for CS445 Compilers
# Jacob Friedberg
# Version 1.0
SRCS = scanner.l parser.y ourgetopt.cpp Tree.cpp
HDRS = scanType.h ourgetopt.h Tree.h
OBJS = lex.yy.o parser.tab.o ourgetopt.o Tree.o
BIN  = c-
CC   = g++
CPPFLAGS = -std=c++11 -Wall -Wextra -pedantic -g
LEX = flex
#-Wcounterexamples
BISONFLAGS = -v  -t -d
TARNAME = pas02.tar

$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(BIN)
	
parser.tab.h parser.tab.c: parser.y
	bison $(BISONFLAGS) parser.y   # -d supplies defines file, -v supplies output

lex.yy.c: scanner.l parser.tab.h
	$(LEX) scanner.l  # -d debug

all:    
	touch $(SRCS)
	make


.PHONY : clean
clean:
	@echo "cleaning..."
	rm -f $(BIN) $(OBJS) lex.yy.c parser.tab.c parser.tab.h parser.output *~
	rm -rf $(TARNAME)
.PHONY : tar
tar:
	@echo "Taring in progress..."
	tar -cvf $(TARNAME) $(SRCS) $(HDRS) makefile 
	ls -l $(TARNAME)