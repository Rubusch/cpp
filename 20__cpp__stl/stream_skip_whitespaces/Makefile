# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = skipwhitespaces.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

skipwhitespaces.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: skipwhitespaces.exe

clean:
	${RM} $(OBJECTS) skipwhitespaces.exe *~ core


