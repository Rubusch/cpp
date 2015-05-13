# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = getint.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

getint.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: getint.exe

clean: 
	${RM} $(OBJECTS) getint.exe *~ core


