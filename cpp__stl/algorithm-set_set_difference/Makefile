# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = setdifference.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

setdifference.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: setdifference.exe

clean:
	${RM} $(OBJECTS) setdifference.exe *~ core


