# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = virtualnonvirtualinheritance.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

virtualnonvirtualinheritance.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: virtualnonvirtualinheritance.exe

clean:
	${RM} $(OBJECTS) virtualnonvirtualinheritance.exe *~ core


