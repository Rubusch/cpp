# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = opsubscript.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

opsubscript.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: opsubscript.exe

clean: 
	${RM} $(OBJECTS) opsubscript.exe opsubscript.exe.stackdump *~ core


