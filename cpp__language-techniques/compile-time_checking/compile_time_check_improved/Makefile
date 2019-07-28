# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = improvederrormessage.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

improvederrormessage.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: improvederrormessage.exe

clean:
	${RM} $(OBJECTS) improvederrormessage.exe *~ core


