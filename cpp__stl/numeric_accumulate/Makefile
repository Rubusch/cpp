# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = accumulate.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

accumulate.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: accumulate.exe

clean:
	${RM} $(OBJECTS) accumulate.exe *~ core


