# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = int2type.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

int2type.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: int2type.exe

clean: 
	${RM} $(OBJECTS) int2type.exe *~ core


