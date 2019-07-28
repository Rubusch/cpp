# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = opequality.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

opequality.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: opequality.exe

clean:
	${RM} $(OBJECTS) opequality.exe *~ core


