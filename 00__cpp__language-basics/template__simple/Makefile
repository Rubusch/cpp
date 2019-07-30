# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = templatesimple.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

templatesimple.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: templatesimple.exe

clean:
	${RM} $(OBJECTS) templatesimple.exe *~ core

.PHONY: clean
