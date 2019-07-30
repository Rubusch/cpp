# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = exception2.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

exception2.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: exception2.exe

clean:
	${RM} $(OBJECTS) exception2.exe *~ core


