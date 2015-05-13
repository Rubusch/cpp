# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = complex.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

complex.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: complex.exe

clean: 
	${RM} $(OBJECTS) complex.exe *~ core


