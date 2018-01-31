# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = mismatch.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

mismatch.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: mismatch.exe

clean:
	${RM} $(OBJECTS) mismatch.exe *~ core


