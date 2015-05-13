# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = inserter.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

inserter.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: inserter.exe

clean: 
	${RM} $(OBJECTS) inserter.exe *~ core


