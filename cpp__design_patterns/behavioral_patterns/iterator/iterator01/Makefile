# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  iterator.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

iterator.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: iterator.exe

clean:
	${RM} $(OBJECTS) iterator.exe *~ core


