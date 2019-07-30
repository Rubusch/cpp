# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = noreferenceonlocals.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

noreferenceonlocals.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: noreferenceonlocals.exe

clean:
	${RM} $(OBJECTS) noreferenceonlocals.exe *~ core


