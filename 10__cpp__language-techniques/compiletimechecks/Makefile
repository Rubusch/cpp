# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = compiletimechecks.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

compiletimechecks.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: compiletimechecks.exe

clean:
	${RM} $(OBJECTS) compiletimechecks.exe *~ core


