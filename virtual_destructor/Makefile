# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = virtualdestructor.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

virtualdestructor.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: virtualdestructor.exe

clean:
	${RM} $(OBJECTS) virtualdestructor.exe *~ core


