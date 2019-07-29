# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = swap.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

swap.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: swap.exe

clean:
	${RM} $(OBJECTS) swap.exe *~ core


