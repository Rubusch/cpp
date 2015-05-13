# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = min.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

min.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: min.exe

clean: 
	${RM} $(OBJECTS) min.exe *~ core


