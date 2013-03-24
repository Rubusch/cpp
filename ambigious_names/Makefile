# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = ambiguous.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

ambiguous.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: ambiguous.exe

clean: 
	${RM} $(OBJECTS) ambiguous.exe *~ core


