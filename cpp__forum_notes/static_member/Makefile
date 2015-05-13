# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE =  static.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

static.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: static.exe

clean: 
	${RM} $(OBJECTS) static.exe *~ core


