# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = opstreams.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

opstreams.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: opstreams.exe

clean: 
	${RM} $(OBJECTS) opstreams.exe opstreams.exe.stackdump *~ core


