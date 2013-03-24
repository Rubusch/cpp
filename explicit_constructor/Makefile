# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = explicitconstructor.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

explicitconstructor.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: explicitconstructor.exe

clean: 
	${RM} $(OBJECTS) explicitconstructor.exe *~ core


