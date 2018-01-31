# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = adjacentdifference.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

adjacentdifference.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: adjacentdifference.exe

clean:
	${RM} $(OBJECTS) adjacentdifference.exe *~ core


