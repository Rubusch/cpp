# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = randomshuffle.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

randomshuffle.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: randomshuffle.exe

clean:
	${RM} $(OBJECTS) randomshuffle.exe *~ core


