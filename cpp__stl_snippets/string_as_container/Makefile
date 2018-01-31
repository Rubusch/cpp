# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = stringascontainer.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

stringascontainer.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: stringascontainer.exe

clean:
	${RM} $(OBJECTS) stringascontainer.exe *~ core


