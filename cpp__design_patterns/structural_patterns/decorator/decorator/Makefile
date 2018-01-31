# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = decorator.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

decorator.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: decorator.exe

clean:
	${RM} $(OBJECTS) decorator.exe *~ core


