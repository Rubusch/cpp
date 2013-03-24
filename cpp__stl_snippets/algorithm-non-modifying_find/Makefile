# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = find.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

find.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: find.exe

clean: 
	${RM} $(OBJECTS) find.exe *~ core


