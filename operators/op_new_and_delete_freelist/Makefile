# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = freelist.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

freelist.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: freelist.exe

clean: 
	${RM} $(OBJECTS) freelist.exe *~ core


