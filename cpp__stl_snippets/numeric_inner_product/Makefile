# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = innerproduct.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

innerproduct.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: innerproduct.exe

clean: 
	${RM} $(OBJECTS) innerproduct.exe *~ core


