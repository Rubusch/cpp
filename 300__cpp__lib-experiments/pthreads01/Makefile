# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = test.cpp
HEADERS = test.h
OBJECTS = ${SOURCE:.c=.o}

.PREFIXES = .c .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.c.o:
	${CC} -c ${CFLAGS} $<

test.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm -pthread

all: test.exe

clean:
	${RM} *.o test.exe *~ core


