# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = virtualvirtualdestructor.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

virtualvirtualdestructor.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: virtualvirtualdestructor.exe

clean:
	${RM} $(OBJECTS) virtualvirtualdestructor.exe *~ core


