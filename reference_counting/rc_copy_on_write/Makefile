# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = rc_copyonwrite.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

rc_copyonwrite.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: rc_copyonwrite.exe

clean: 
	${RM} $(OBJECTS) rc_copyonwrite.exe *~ core


