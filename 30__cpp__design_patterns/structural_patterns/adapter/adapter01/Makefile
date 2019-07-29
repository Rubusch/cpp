# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = adapter.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

adapter.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: adapter.exe

clean:
	${RM} $(OBJECTS) adapter.exe *~ core


