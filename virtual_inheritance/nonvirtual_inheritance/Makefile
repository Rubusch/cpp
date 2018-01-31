# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = nonvirtualinheritance.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

nonvirtualinheritance.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: nonvirtualinheritance.exe

clean:
	${RM} $(OBJECTS) nonvirtualinheritance.exe *~ core


