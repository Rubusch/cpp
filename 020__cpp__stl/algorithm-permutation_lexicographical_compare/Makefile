# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = lexicographicalcompare.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

lexicographicalcompare.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: lexicographicalcompare.exe

clean:
	${RM} $(OBJECTS) lexicographicalcompare.exe *~ core


