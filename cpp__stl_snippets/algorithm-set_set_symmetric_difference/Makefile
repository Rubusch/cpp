# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = setsymmetricdifference.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

setsymmetricdifference.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: setsymmetricdifference.exe

clean:
	${RM} $(OBJECTS) setsymmetricdifference.exe *~ core


