# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = stringstream.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

stringstream.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: stringstream.exe

clean: 
	${RM} $(OBJECTS) stringstream.exe *~ core


