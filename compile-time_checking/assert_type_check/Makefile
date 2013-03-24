# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = typecheck.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

typecheck.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: typecheck.exe

clean: 
	${RM} $(OBJECTS) typecheck.exe *~ core


