# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = reverse.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

reverse.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: reverse.exe

clean:
	${RM} $(OBJECTS) reverse.exe *~ core


