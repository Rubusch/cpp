# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = stablesort.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

stablesort.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: stablesort.exe

clean:
	${RM} $(OBJECTS) stablesort.exe *~ core


