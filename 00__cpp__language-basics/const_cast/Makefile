# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = constcast.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

constcast.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: constcast.exe

clean:
	${RM} $(OBJECTS) constcast.exe *~ core


