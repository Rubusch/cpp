# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = valarray.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

valarray.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: valarray.exe

clean: 
	${RM} $(OBJECTS) valarray.exe *~ core


