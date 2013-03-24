# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = ifstream.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

ifstream.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: ifstream.exe

clean: 
	${RM} $(OBJECTS) ifstream.exe *~ ifstream.exe.stackdump core


