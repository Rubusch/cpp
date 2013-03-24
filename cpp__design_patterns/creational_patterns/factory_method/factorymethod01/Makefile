# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = factorymethod.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

factorymethod.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: factorymethod.exe

clean: 
	${RM} $(OBJECTS) factorymethod.exe *~ core


