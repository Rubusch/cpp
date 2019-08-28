# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = conversion.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

conversion.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: conversion.exe

clean:
	${RM} $(OBJECTS) conversion.exe *~ core


