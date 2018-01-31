# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = type2type.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

type2type.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: type2type.exe

clean:
	${RM} $(OBJECTS) type2type.exe *~ core


