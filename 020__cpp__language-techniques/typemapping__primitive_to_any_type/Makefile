# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = typemappingprimitivetoanytype.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

typemappingprimitivetoanytype.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: typemappingprimitivetoanytype.exe

clean:
	${RM} $(OBJECTS) typemappingprimitivetoanytype.exe *~ core


