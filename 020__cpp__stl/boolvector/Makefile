# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = boolvector.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

boolvector.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: boolvector.exe

clean:
	${RM} $(OBJECTS) boolvector.exe *~ core


