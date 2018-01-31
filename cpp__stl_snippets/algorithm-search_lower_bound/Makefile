# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = lowerbound.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

lowerbound.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: lowerbound.exe

clean:
	${RM} $(OBJECTS) lowerbound.exe *~ core


