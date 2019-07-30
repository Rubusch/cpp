# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = newdelete1.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

newdelete1.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: newdelete1.exe

clean:
	${RM} $(OBJECTS) newdelete1.exe *~ core


