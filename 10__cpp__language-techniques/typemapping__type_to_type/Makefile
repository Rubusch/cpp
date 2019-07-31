# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = typemappingtypetotype.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

typemappingtypetotype.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: typemappingtypetotype.exe

clean:
	${RM} $(OBJECTS) typemappingtypetotype.exe *~ core


