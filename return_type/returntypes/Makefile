# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = returntype.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

returntype.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: returntype.exe

clean: 
	${RM} $(OBJECTS) returntype.exe *~ core


