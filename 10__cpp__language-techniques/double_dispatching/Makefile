# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  doubledispatching.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

doubledispatching.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: doubledispatching.exe

clean:
	${RM} $(OBJECTS) doubledispatching.exe *~ core


