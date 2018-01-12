# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = bridge.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

bridge.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: bridge.exe

clean:
	${RM} $(OBJECTS) bridge.exe *~ core


