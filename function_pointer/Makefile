# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE =  functionpointer.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

functionpointer.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: functionpointer.exe

clean: 
	${RM} $(OBJECTS) functionpointer.exe *~ core


