# MakeFile for CS445 Compilers
# Jacob Friedberg
# Version 1.0
SRCS = scanner.l parser.y
HDRS = scanType.h
OBJS = lex.yy.o parser.tab.o
BIN  = c-
CC   = g++
CPPFLAGS = -std=c++11 -Wall -Wextra -pedantic
LEX = flex
LEXFLAGS = 

$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(BIN)
	
parser.tab.h parser.tab.c: parser.y
	bison -v -t -d parser.y   # -d supplies defines file, -v supplies output

lex.yy.c: scanner.l parser.tab.h
	$(LEX) scanner.l  # -d debug

all:    
	touch $(SRCS)
	make



#$(BIN): $(OBJS)
	#$(CC) $(CPPFLAGS) $(OBJS) $(LIBS) -o $(BIN)
#
#$(OBJS): $(HDRS)

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