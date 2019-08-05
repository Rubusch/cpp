# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = compiletimechecksimproved.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

compiletimechecksimproved.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: compiletimechecksimproved.exe

clean:
	${RM} $(OBJECTS) compiletimechecksimproved.exe *~ core


