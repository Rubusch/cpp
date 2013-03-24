# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = bind2nd.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

bind2nd.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: bind2nd.exe

clean: 
	${RM} $(OBJECTS) bind2nd.exe *~ core


