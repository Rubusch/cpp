# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = typelist.cpp
HEADERS = conversion.hpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

typelist.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: typelist.exe

clean: 
	${RM} $(OBJECTS) typelist.exe *~ core


