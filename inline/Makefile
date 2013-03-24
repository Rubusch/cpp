# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = inline.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

inline.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: inline.exe

clean: 
	${RM} $(OBJECTS) inline.exe *~ core


