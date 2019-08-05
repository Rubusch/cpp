# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = compiletimechecksasserttypecheck.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

compiletimechecksasserttypecheck.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: compiletimechecksasserttypecheck.exe

clean:
	${RM} $(OBJECTS) compiletimechecksasserttypecheck.exe *~ core


