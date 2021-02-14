# MakeFile for CS445 Compilers
# Jacob Friedberg
# Version 1.0
SRCS = scanner.l parser.y ourgetopt.cpp
HDRS = scanType.h ourgetopt.h
OBJS = lex.yy.o parser.tab.o ourgetopt.o
BIN  = c-
CC   = g++
CPPFLAGS = -std=c++11 -Wall -Wextra -pedantic
LEX = flex
LEXFLAGS = 

$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(BIN)
	
parser.tab.h parser.tab.c: parser.y
	bison -Wcounterexamples -v  -t -d parser.y   # -d supplies defines file, -v supplies output

lex.yy.c: scanner.l parser.tab.h
	$(LEX) scanner.l  # -d debug

all:    
	touch $(SRCS)
	make


.PHONY : clean
clean:
	@echo "cleaning..."
	rm -f $(BIN) $(OBJS) lex.yy.c parser.tab.c parser.tab.h parser.output *~
	rm -rf pas01.tar
.PHONY : tar
tar:
	@echo "Taring in progress..."
	tar -cvf pas01.tar $(SRCS) $(HDRS) makefile 
	ls -l pas01.tar