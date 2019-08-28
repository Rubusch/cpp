# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = binarysearch.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

binarysearch.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: binarysearch.exe

clean:
	${RM} $(OBJECTS) binarysearch.exe *~ core


