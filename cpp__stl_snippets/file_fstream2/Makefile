# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = fstream.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

fstream.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: fstream.exe

clean: 
	${RM} $(OBJECTS) fstream.exe Jack.txt *~ core


