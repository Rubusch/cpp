# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  interpreter.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

interpreter.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: interpreter.exe

clean:
	${RM} $(OBJECTS) interpreter.exe *~ core


