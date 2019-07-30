# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = operatorsassignment.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

operatorsassignment.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: operatorsassignment.exe

clean:
	${RM} $(OBJECTS) operatorsassignment.exe *~ core


