# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = newhandler.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

newhandler.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: newhandler.exe

clean:
	${RM} $(OBJECTS) newhandler.exe *~ core


