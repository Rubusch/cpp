# Makefile for C++ Class
SOURCE	= main.cpp alpha.cpp\
	beta.cpp
HEADERS	= alpha.h beta.h
OBJECTS	= ${SOURCE:.cpp=.o}

.PREFIXES	= .cpp .o
CC		= g++
CPPFLAGS	= -g -Wall -funsigned-char
RM		= rm -f
MV		= mv -f
CP		= cp -f

.cpp.o:
	${CC} -c ${CPPFLAGS} $<

start: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: start

clean:
	-${RM} start *.o *~ core
