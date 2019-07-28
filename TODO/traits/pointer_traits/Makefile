# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = pointertraits.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

pointertraits.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: pointertraits.exe

clean:
	${RM} $(OBJECTS) pointertraits.exe *~ core


