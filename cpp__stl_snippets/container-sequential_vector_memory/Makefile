# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = vectormemory.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

vectormemory.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: vectormemory.exe

clean: 
	${RM} $(OBJECTS) vectormemory.exe *~ core


