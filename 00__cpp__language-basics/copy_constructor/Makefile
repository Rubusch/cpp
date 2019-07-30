# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = copyconstructor.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

copyconstructor.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: copyconstructor.exe

clean:
	${RM} $(OBJECTS) copyconstructor.exe *~ core


