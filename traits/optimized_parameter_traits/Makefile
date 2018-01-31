# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = parametertraits.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

parametertraits.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: parametertraits.exe

clean:
	${RM} $(OBJECTS) parametertraits.exe *~ core


