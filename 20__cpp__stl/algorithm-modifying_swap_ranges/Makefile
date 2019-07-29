# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = swapranges.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

swapranges.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: swapranges.exe

clean:
	${RM} $(OBJECTS) swapranges.exe *~ core


