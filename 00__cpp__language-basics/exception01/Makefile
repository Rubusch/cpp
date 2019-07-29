# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = exception.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

exception.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: exception.exe

clean:
	${RM} $(OBJECTS) exception.exe *~ core


