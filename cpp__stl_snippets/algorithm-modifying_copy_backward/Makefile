# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = copybackward.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

copybackward.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: copybackward.exe

clean: 
	${RM} $(OBJECTS) copybackward.exe *~ core


