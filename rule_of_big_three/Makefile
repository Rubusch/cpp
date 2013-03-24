# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = ruleofthree.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

ruleofthree.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: ruleofthree.exe

clean: 
	${RM} $(OBJECTS) ruleofthree.exe *~ core


