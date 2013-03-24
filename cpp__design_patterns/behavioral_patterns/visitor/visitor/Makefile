# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE =  visitor.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

visitor.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: visitor.exe

clean: 
	${RM} $(OBJECTS) visitor.exe *~ core


