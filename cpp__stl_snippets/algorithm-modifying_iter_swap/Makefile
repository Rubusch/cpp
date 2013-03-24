# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = iterswap.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

iterswap.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: iterswap.exe

clean: 
	${RM} $(OBJECTS) iterswap.exe *~ core


