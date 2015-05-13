# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = bitset.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

bitset.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: bitset.exe

clean: 
	${RM} $(OBJECTS) bitset.exe *~ core


