# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = dequetest.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

dequetest.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: dequetest.exe

clean:
	${RM} $(OBJECTS) dequetest.exe *~ core


