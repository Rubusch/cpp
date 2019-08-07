# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = lambda.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

lambda.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: lambda.exe

clean:
	${RM} $(OBJECTS) lambda.exe *~ core


