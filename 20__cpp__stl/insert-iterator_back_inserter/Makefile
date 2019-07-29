# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = backinserter.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

backinserter.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: backinserter.exe

clean:
	${RM} $(OBJECTS) backinserter.exe *~ core


