# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = setunion.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

setunion.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: setunion.exe

clean:
	${RM} $(OBJECTS) setunion.exe *~ core


