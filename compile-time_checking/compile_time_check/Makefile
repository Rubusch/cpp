# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = compiletimeerror.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

compiletimeerror.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: compiletimeerror.exe

clean: 
	${RM} $(OBJECTS) compiletimeerror.exe *~ core


