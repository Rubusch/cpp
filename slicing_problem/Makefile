# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = slicingproblem.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

slicingproblem.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: slicingproblem.exe

clean: 
	${RM} $(OBJECTS) slicingproblem.exe *~ core


