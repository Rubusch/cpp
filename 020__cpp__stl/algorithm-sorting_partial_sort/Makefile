# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = partialsort.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

partialsort.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: partialsort.exe

clean:
	${RM} $(OBJECTS) partialsort.exe *~ core


