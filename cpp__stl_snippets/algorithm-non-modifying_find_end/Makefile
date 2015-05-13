# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = findend.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

findend.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: findend.exe

clean: 
	${RM} $(OBJECTS) findend.exe *~ core


