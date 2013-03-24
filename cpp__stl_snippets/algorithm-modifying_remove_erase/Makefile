# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = removeerase.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

removeerase.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: removeerase.exe

clean: 
	${RM} $(OBJECTS) removeerase.exe *~ core


