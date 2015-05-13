# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE =  callback.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

callback.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: callback.exe

clean: 
	${RM} $(OBJECTS) callback.exe *~ core


