# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = setintersection.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

setintersection.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: setintersection.exe

clean:
	${RM} $(OBJECTS) setintersection.exe *~ core


