# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = opassignment.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

opassignment.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: opassignment.exe

clean:
	${RM} $(OBJECTS) opassignment.exe *~ core


