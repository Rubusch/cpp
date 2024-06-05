## Makefile for C++ Class
## needs g++ version >= g++-5
SOURCE	= main.cc
OBJECTS	= ${SOURCE:.cc=.o}

.PREFIXES	= .cc .o
CXX		= g++
CXXFLAGS	= -std=c++14 -g -Wall #-funsigned-char
RM		= rm -f

main.exe: ${OBJECTS}
	${CXX} -o $@ ${CXXFLAGS} $<

all: main.exe

clean:
	-${RM} main.exe *.o *~ core
