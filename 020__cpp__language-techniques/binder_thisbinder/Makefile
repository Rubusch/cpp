# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = binderthisbinder.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

binderthisbinder.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: binderthisbinder.exe

clean:
	${RM} $(OBJECTS) binderthisbinder.exe *~ core

.PHONY: clean

