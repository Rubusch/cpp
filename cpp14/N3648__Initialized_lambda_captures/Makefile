# Makefile for C++ Class
SOURCE	= main.cc
OBJECTS	= ${SOURCE:.cc=.o}

.PREFIXES	= .cc .o
CXX		= g++-5
#CXX		= clang++-3.5
CXXFLAGS	= -std=c++14 -g -Wall #-funsigned-char
RM		= rm -f

main.exe: ${OBJECTS}
	${CXX} -o $@ ${CXXFLAGS} $<

all: main.exe

clean:
	-${RM} main.exe *.o *~ core
