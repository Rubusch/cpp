# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = equal.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

equal.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: equal.exe

clean:
	${RM} $(OBJECTS) equal.exe *~ core


