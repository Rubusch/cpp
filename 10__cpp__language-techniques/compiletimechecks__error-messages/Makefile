# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = compiletimecheckserrormessages.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

compiletimecheckserrormessages.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: compiletimecheckserrormessages.exe

clean:
	${RM} $(OBJECTS) compiletimecheckserrormessages.exe *~ core


