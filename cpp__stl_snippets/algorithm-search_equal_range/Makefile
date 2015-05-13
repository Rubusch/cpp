# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = equalrange.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

equalrange.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: equalrange.exe

clean: 
	${RM} $(OBJECTS) equalrange.exe *~ core


