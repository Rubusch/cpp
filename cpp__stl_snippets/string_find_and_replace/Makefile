# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = string.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

string.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: string.exe

clean: 
	${RM} $(OBJECTS) string.exe *~ core


