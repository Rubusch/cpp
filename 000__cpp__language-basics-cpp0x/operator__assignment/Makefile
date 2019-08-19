# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = operatorassignment.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

operatorassignment.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: operatorassignment.exe

clean:
	${RM} $(OBJECTS) operatorassignment.exe *~ core


