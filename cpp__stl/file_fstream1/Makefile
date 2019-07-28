# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = fstreams.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

fstreams.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: fstreams.exe

clean:
	${RM} $(OBJECTS) fstreams.exe Jack.txt *~ core


