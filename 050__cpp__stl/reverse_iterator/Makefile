# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = findreverse.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

findreverse.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: findreverse.exe

clean:
	${RM} $(OBJECTS) findreverse.exe *~ core


