# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  doubledispatch.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

doubledispatch.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: doubledispatch.exe

clean:
	${RM} $(OBJECTS) doubledispatch.exe *~ core


