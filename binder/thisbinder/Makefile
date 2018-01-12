# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = binder.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

binder.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: binder.exe

clean:
	${RM} $(OBJECTS) binder.exe *~ core

.PHONY: clean

