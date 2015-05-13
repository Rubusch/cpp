# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = nulltype.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

nulltype.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: nulltype.exe

clean: 
	${RM} $(OBJECTS) nulltype.exe *~ core


