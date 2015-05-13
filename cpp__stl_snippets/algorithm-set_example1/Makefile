# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = example.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

example.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: example.exe

clean: 
	${RM} $(OBJECTS) example.exe *~ core


