# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = includes.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

includes.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: includes.exe

clean:
	${RM} $(OBJECTS) includes.exe *~ core


