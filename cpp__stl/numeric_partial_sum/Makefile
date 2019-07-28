# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = partialsum.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

partialsum.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: partialsum.exe

clean:
	${RM} $(OBJECTS) partialsum.exe *~ core


