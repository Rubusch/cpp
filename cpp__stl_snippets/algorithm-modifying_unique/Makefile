# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = unique.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

unique.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: unique.exe

clean: 
	${RM} $(OBJECTS) unique.exe *~ core


