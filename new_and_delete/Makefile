# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = newanddelete.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

newanddelete.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: newanddelete.exe

clean:
	${RM} $(OBJECTS) newanddelete.exe *~ core


