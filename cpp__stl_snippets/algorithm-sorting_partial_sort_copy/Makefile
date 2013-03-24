# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = partialsortcopy.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

partialsortcopy.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: partialsortcopy.exe

clean: 
	${RM} $(OBJECTS) partialsortcopy.exe *~ core


