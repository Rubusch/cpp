# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = memorypool.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

memorypool.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: memorypool.exe

clean: 
	${RM} $(OBJECTS) memorypool.exe *~ core


