# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = ruleofbigthree.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

ruleofbigthree.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: ruleofbigthree.exe

clean:
	${RM} $(OBJECTS) ruleofbigthree.exe *~ core


