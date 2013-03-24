# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = heap.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

heap.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: heap.exe

clean: 
	${RM} $(OBJECTS) heap.exe *~ core


