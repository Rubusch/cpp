# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = norefonlocals.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

norefonlocals.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: norefonlocals.exe

clean: 
	${RM} $(OBJECTS) norefonlocals.exe *~ core


