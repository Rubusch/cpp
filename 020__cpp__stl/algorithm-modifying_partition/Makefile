# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = partition.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

partition.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: partition.exe

clean:
	${RM} $(OBJECTS) partition.exe *~ core


