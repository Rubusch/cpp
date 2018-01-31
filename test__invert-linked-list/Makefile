# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = invert-linked-list.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

invert.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: invert.exe

clean:
	${RM} $(OBJECTS) invert.exe *~ core


