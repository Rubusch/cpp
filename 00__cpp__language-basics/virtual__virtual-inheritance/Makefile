# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = virtualinheritance.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

virtualinheritance.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: virtualinheritance.exe

clean:
	${RM} $(OBJECTS) virtualinheritance.exe *~ core


