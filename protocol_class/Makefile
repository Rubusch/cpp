# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = protocol.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

protocol.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: protocol.exe

clean: 
	${RM} $(OBJECTS) protocol.exe *~ core


