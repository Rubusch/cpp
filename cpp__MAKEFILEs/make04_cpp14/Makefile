# Makefile for C++ Class
SOURCE	= main.cc alpha.cc\
	beta.cc
HEADERS	= alpha.h beta.h
OBJECTS	= ${SOURCE:.cc=.o}

.PREFIXES	= .cc .o
CXX		= g++-5
CXXFLAGS	= -std=c++14 -g -Wall -funsigned-char
RM		= rm -f

.cc.o:
	${CXX} -c ${CXXFLAGS} $<

start: ${OBJECTS}
	${CXX} -o $@ ${OBJECTS} -lm

all: start

clean:
	-${RM} start *.o *~ core
