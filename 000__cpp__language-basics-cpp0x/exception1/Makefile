# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = exception1.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

exception1.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: exception1.exe

clean:
	${RM} $(OBJECTS) exception1.exe *~ core


