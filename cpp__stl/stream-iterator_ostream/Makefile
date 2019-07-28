# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = ostreamiterator.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

ostreamiterator.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: ostreamiterator.exe

clean:
	${RM} $(OBJECTS) ostreamiterator.exe *~ core


