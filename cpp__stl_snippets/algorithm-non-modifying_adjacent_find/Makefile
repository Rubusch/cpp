# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = adjacentfind.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

adjacentfind.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: adjacentfind.exe

clean: 
	${RM} $(OBJECTS) adjacentfind.exe *~ core


