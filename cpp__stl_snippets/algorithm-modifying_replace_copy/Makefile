# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = replacecopy.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

replacecopy.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: replacecopy.exe

clean: 
	${RM} $(OBJECTS) replacecopy.exe *~ core


