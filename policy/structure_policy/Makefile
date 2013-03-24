# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE =  structurepolicy.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

structurepolicy.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: structurepolicy.exe

clean: 
	${RM} $(OBJECTS) structurepolicy.exe *~ core


