# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = operatorequals.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

operatorequals.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: operatorequals.exe

clean:
	${RM} $(OBJECTS) operatorequals.exe *~ core


