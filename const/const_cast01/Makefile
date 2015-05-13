# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = const.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

const.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: const.exe

clean: 
	${RM} $(OBJECTS) const.exe *~ core


