# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = permutation.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

permutation.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: permutation.exe

clean: 
	${RM} $(OBJECTS) permutation.exe *~ permutation.exe.stackdump core


