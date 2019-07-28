# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = fill.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

fill.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: fill.exe

clean:
	${RM} $(OBJECTS) fill.exe *~ core


