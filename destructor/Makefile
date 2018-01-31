# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = destructoranddelete.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

destructoranddelete.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: destructoranddelete.exe

clean:
	${RM} $(OBJECTS) destructoranddelete.exe *~ core


