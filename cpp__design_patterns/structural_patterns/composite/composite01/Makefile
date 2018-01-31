# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = composite.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

composite.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: composite.exe

clean:
	${RM} $(OBJECTS) composite.exe *~ core


