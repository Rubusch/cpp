# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE =  functor.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

functor.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: functor.exe

clean: 
	${RM} $(OBJECTS) functor.exe *~ core


