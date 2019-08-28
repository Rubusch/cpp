# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = reversecopy.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

reversecopy.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: reversecopy.exe

clean:
	${RM} $(OBJECTS) reversecopy.exe *~ core


