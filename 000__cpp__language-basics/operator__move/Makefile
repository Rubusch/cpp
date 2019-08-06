# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = operatormove.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

operatormove.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: operatormove.exe

clean:
	${RM} $(OBJECTS) operatormove.exe *~ core


