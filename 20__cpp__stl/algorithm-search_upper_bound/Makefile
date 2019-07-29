# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = upperbound.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

upperbound.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: upperbound.exe

clean:
	${RM} $(OBJECTS) upperbound.exe *~ core


