# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = matrix.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

matrix.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: matrix.exe

clean: 
	${RM} $(OBJECTS) matrix.exe *~ core


