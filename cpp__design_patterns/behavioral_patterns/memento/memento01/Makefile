# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  memento.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

memento.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: memento.exe

clean:
	${RM} $(OBJECTS) memento.exe *~ core


