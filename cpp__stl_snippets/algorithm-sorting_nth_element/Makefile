# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = nthelement.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

nthelement.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: nthelement.exe

clean: 
	${RM} $(OBJECTS) nthelement.exe *~ core


