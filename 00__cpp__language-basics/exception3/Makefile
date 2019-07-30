# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = exception3.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

exception3.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: exception3.exe

clean:
	${RM} $(OBJECTS) exception3.exe *~ core


