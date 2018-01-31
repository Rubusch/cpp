# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  mediator.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

mediator.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: mediator.exe

clean:
	${RM} $(OBJECTS) mediator.exe *~ core


