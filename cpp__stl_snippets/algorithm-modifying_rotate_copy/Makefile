# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = rotatecopy.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

rotatecopy.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: rotatecopy.exe

clean: 
	${RM} $(OBJECTS) rotatecopy.exe *~ core


