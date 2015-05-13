# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = errormessage.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

errormessage.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: errormessage.exe

clean: 
	${RM} $(OBJECTS) errormessage.exe *~ core


