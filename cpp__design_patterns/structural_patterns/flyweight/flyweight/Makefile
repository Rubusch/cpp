# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = flyweight.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

flyweight.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: flyweight.exe

clean:
	${RM} $(OBJECTS) flyweight.exe *~ core


