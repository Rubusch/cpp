# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = ambiguousnames.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

ambiguousnames.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: ambiguousnames.exe

clean:
	${RM} $(OBJECTS) ambiguousnames.exe *~ core


