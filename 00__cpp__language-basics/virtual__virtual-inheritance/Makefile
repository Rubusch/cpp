# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = virtualvirtualinheritance.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

virtualvirtualinheritance.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: virtualvirtualinheritance.exe

clean:
	${RM} $(OBJECTS) virtualvirtualinheritance.exe *~ core


