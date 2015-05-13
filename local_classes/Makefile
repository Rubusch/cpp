# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = localclass.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

localclass.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: localclass.exe

clean: 
	${RM} $(OBJECTS) localclass.exe *~ core


