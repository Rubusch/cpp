# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = foreach.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

foreach.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: foreach.exe

clean: 
	${RM} $(OBJECTS) foreach.exe *~ core


