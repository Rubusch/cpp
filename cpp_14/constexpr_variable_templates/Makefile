# Makefile for C++ Class
SOURCE	= main.cc
#HEADERS	=
OBJECTS	= ${SOURCE:.cc=.o}

.PREFIXES	= .cc .o
CXX		= g++-5
CXXFLAGS	= -std=c++14 -g -Wall #-funsigned-char
RM		= rm -f

## TODO multi file case
## TODO update make templates to .cc !!!
# .cc.o:
# 	${CXX} -c ${CXXFLAGS} $<

# main: ${OBJECTS}
# 	${CXX} -o $@ ${OBJECTS} -lm


main: ${OBJECTS}
	${CXX} -o $@ ${CXXFLAGS} $<

all: main

clean:
	-${RM} main *.o *~ core
