# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = typemappingstepexample.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

typemappingstepexample.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: typemappingstepexample.exe

clean:
	${RM} $(OBJECTS) typemappingstepexample.exe *~ core


