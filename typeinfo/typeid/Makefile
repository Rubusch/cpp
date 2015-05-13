# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = typeid.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

typeid.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: typeid.exe

clean: 
	${RM} $(OBJECTS) typeid.exe *~ core


