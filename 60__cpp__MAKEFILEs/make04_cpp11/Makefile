# Makefile for C++ Class
SOURCE	= main.cc alpha.cc\
	beta.cc
HEADERS	= alpha.h beta.h
OBJECTS	= ${SOURCE:.cc=.o}

.PREFIXES	= .cc .o
CXX		= g++-5
CXXFLAGS	= -std=c++11 -g -Wall -funsigned-char
RM		= rm -f
MV		= mv -f
CP		= cp -f

.cc.o:
	${CXX} -c ${CXXFLAGS} $<

start: ${OBJECTS}
	${CXX} -o $@ ${OBJECTS} -lm

all: start

clean:
	-${RM} start *.o *~ core
