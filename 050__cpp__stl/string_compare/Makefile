# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = strcmp.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

stringcompare.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: stringcompare.exe

clean:
	${RM} $(OBJECTS) stringcompare.exe *~ core


